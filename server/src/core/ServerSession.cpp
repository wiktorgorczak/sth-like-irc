#include "ServerSession.h"
#include "../models/Response.h"
#include "../exceptions/InternalError.h"

bool quitFlag = false;

ServerSession::ServerSession(std::ifstream &configFile, std::ifstream &usersFile, std::ifstream &roomsFile) {
    ConfigurationParser configurationParser;
    UserRepositoryParser userRepositoryParser;
    quitFlag = false;
    userParser = new UserParser();
    currentThreads = new int;
    *currentThreads = 0;

    try {
        configuration = configurationParser.parseFrom(configFile);
        userRepository = userRepositoryParser.parseFrom(usersFile);

        RoomRepositoryParser roomRepositoryParser(userRepository);
        roomRepository = roomRepositoryParser.parseFrom(roomsFile);
    } catch(ParsingError &exception) {
        std::cerr << "Could not initialize server configuration due to parsing error." << std::endl;
        throw InitServerError();
    }
    messageParser = new MessageParser(roomRepository);

    sockets = new int[configuration->getMaxThreadCount()];

    for(int i = 0; i < configuration->getMaxThreadCount(); i++) {
        sockets[i] = -1;
    }

    initSignalHandler();
    serverSocketDescriptor = init();
}

ServerSession::~ServerSession() {
    delete messageParser;
    delete userParser;
    delete currentThreads;
    delete configuration;
    delete userRepository;
    delete roomRepository;
    delete[] sockets;
}

void ServerSession::initSignalHandler() {
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = quitSignalHandler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, nullptr);
}

void quitSignalHandler(int signal) {
    quitFlag = true;
}

int ServerSession::init() {
    std::cout << "Initializing server socket...";
    struct sockaddr_in serverAddress;
    char reuseAddrValue = 1;

    memset(&serverAddress, 0, sizeof(struct sockaddr));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(configuration->getServerPort());

    serverSocketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocketDescriptor < 0) {
        std::cout << "Could not create socket.\t[ERROR]" << std::endl;
        throw InitServerError();
    }

    setsockopt(serverSocketDescriptor, SOL_SOCKET, SO_REUSEADDR,
               (char*)&reuseAddrValue, sizeof(struct sockaddr));
    int bindResult = bind(serverSocketDescriptor,
                          (struct sockaddr*)&serverAddress, sizeof(struct sockaddr));
    if(bindResult < 0) {
        std::cout << "Could not bind IP address to the socket!\t[ERROR]" << std::endl;
        throw InitServerError();
    }

    int listenResult = listen(serverSocketDescriptor, configuration->getQueueSize());
    if(listenResult < 0) {
        std::cout << "An error occurred while trying to set a queue size!\t[ERROR]" << std::endl;
        throw InitServerError();
    }

    std::cout << "\t[OK]" << std::endl;
    return serverSocketDescriptor;
}

void ServerSession::handleConnection(int connectionSocketDescriptor) {
    pthread_t thread;
    auto tData = new ThreadData;
    tData->connectionSocketDescriptor = connectionSocketDescriptor;
    tData->serverSession = this;

    addThread(connectionSocketDescriptor);
    int createThreadResult = pthread_create(&thread, nullptr, threadBehavior, (void*)tData);

    if(createThreadResult < 0) {
        std::cout << "Could not create thread for a connection!\t[ERROR]" << std::endl;
    }
}

bool ServerSession::listenOnSocket(int connectionSocketDescriptor, char buffer[], int bufferSize) {
    bool shouldRemainLoggedIn = false;
    Response response = OK;
    std::string extraContent;
    memset(buffer, '\0', bufferSize);
    if(read(connectionSocketDescriptor, buffer, bufferSize) < 0) { //TODO: implement timeout
        std::cout << "An error occurred while reading to the buffer." << std::endl;
    } else {
        std::string messageText(buffer);
        std::cout << "Content: " << messageText << std::endl;
        try {
            Message *message = messageParser->parseFrom(messageText);

            if(!authorize(message)) {
                response = UNAUTHORIZED;

                delete message->getUser();
            } else {
                shouldRemainLoggedIn = true;
                switch(message->getType()) {
                    case MessageType::STANDARD:
                        sendMessage(message);
                        break;
                    case MessageType::CREATE_ACCOUNT:
                        createAccount(message->getUser());
                        break;
                    case MessageType::JOIN_ROOM:
                        joinRoom(message->getUser(), message->getRoom());
                        break;
                    case MessageType::LEAVE_ROOM:
                        leaveRoom(message->getUser(), message->getRoom());
                        break;
                    case MessageType::SET_STATUS:
                        setStatus(message->getUser(), message->getContent());
                        break;
                    case MessageType::LOGIN:
                        login(message->getUser(), connectionSocketDescriptor);
                        response = AUTHORIZED;
                        break;
                    case MessageType::LOGOFF:
                        logoff(message->getUser());
                        shouldRemainLoggedIn = false;
                        break;
                    case MessageType::GET_ROOMS:
                        extraContent = getAllRooms();
                        break;
                    case MessageType::GET_ROOMS_FOR_USER:
                        extraContent = getRoomsForUser(message->getUser());
                        break;
                    case MessageType::GET_ONLINE_USERS:
                        extraContent = getOnlineUsers(message->getRoom());
                        break;
                }
            }

            delete message;
        } catch(ParsingError& error) {
            std::cout << "Could not parse message!" << std::endl;
            response = PARSING_ERROR;
        } catch(InternalError& error) {
            response = INTERNAL_ERROR;
        }

        sendResponse(response, connectionSocketDescriptor, extraContent);
    }
    return shouldRemainLoggedIn;
}

void* ServerSession::threadBehavior(void *tData) {
    pthread_detach(pthread_self());

    auto threadData = (struct ThreadData*)tData;
    int socket = threadData->connectionSocketDescriptor;
    ServerSession* serverSession = threadData->serverSession;
    int bufferSize = serverSession->getConfiguration()->getBufferSize();
    char* buffer = new char[bufferSize]();

    while(serverSession->listenOnSocket(socket, buffer, bufferSize));

    serverSession->removeThread(socket);
    delete[] buffer;
    delete threadData;
    pthread_exit(nullptr);
}

void ServerSession::run() {
    std::cout << "Server is running on port " << configuration->getServerPort() << std::endl;
    int connectionSocketDescriptor;

    while(!quitFlag) {
        connectionSocketDescriptor = accept(serverSocketDescriptor, nullptr, nullptr);
        std::cout << "Incoming connection..." << std::endl;
        if(connectionSocketDescriptor < 0) {
            std::cout <<"Could not create socket for a connection!\t[ERROR]" << std::endl;
        } else {
            handleConnection(connectionSocketDescriptor);
        }
    }

    close(serverSocketDescriptor);
}

Configuration *ServerSession::getConfiguration() const {
    return configuration;
}

void ServerSession::addThread(int connectionSocketDescriptor) {
    pthread_mutex_lock(&lock);
    while(*currentThreads == configuration->getMaxThreadCount()) {
        pthread_cond_wait(&con, &lock);
    }
    *currentThreads++;

    for(int i = 0; i < configuration->getMaxThreadCount(); i++) {
        if(sockets[i] == -1) {
            sockets[i] = connectionSocketDescriptor;
            break;
        }
    }

    pthread_mutex_unlock(&lock);
}

void ServerSession::removeThread(int connectionSocketDescriptor) {
    pthread_mutex_lock(&lock); //TODO: won't it cause a deadlock?
    for(int i = 0; i < configuration->getMaxThreadCount(); i++) {
        if(sockets[i] == connectionSocketDescriptor) {
            sockets[i] = -1;
            break;
        }
    }
    *currentThreads--;
    pthread_cond_signal(&con);
    pthread_mutex_unlock(&lock);
}

void ServerSession::sendMessage(Message *message) {
    std::string messageText;
    try {
        messageText = messageParser->parseTo(message);
    } catch(ParsingError &error) {
        std::cout << "could not parse message!" << std::endl;
        throw error;
    }

    std::vector<User*>* users = message->getRoom()->getUsers();
    char* buffer = new char[configuration->getBufferSize()]();
    strcpy(buffer, messageText.c_str());

    for(const User* user : *users) {
        if(user->getConnectionSocketDescriptor() > -1) {
            if(write(user->getConnectionSocketDescriptor(), buffer, configuration->getBufferSize()) < 0) {
                std::cout << "Could not send a message from user "
                    + message->getUser()->getName() + "!" << std::endl;
                delete[] buffer;
                throw InternalError();
            }
        }
    }

    delete[] buffer;
}

void ServerSession::joinRoom(User *user, Room *room) {
    room->addUser(user);
}

void ServerSession::leaveRoom(User *user, Room *room) {
    std::vector<User*> *users = room->getUsers();
    users->erase(std::remove(users->begin(), users->end(), user), users->end());
}

void ServerSession::setStatus(User *user, std::string statusStr) {
    UserStatus status = user->getStatus();
    std::transform(statusStr.begin(), statusStr.end(), statusStr.begin(), ::tolower);

    if(statusStr == "online") {
        status = ONLINE;
    } else if(statusStr == "offline") {
        status = OFFLINE;
    } else if(statusStr == "away") {
        status = AWAY;
    }

    user->setStatus(status);
}

void ServerSession::logoff(User *user) {
    setStatus(user, "offline");
    user->setConnectionSocketDescriptor(-1);
}

void ServerSession::login(User *user, int connectionSocketDescriptor) {
    if(user->getConnectionSocketDescriptor() > -1) {
        logoff(user);
    }
    user->setStatus(ONLINE);
    std::cout <<"User " << user->getName() << " logged in!" << std::endl;
    user->setConnectionSocketDescriptor(connectionSocketDescriptor);
}

bool ServerSession::authorize(Message *message) {
    User* actualUser = userRepository->findByName(message->getUser()->getName());

    if(actualUser == nullptr)
        return false;

    if(actualUser->getPassword() == message->getUser()->getPassword()) {
        if(actualUser != message->getUser()) {
            delete message->getUser();
            message->setUser(actualUser);
        }

        return true;
    }

    return false;
}

//void ServerSession::sendResponse(Response response, int connectionSocketDescriptor) {
//    sendResponse(response, connectionSocketDescriptor, "");
//}

void ServerSession::createAccount(User *credentials) {

}

void ServerSession::sendResponse(Response response, int connectionSocketDescriptor, std::string &extraContent) {
    std::string content = "[srv]:";

    switch(response) {
        case Response::OK:
            content += "ok";
            break;
        case Response::AUTHORIZED:
            content += "authorized";
            break;
        case Response::UNAUTHORIZED:
            content += "unauthorized";
            break;
        case Response::PARSING_ERROR:
            content += "parsing_error";
            break;
        case Response::INTERNAL_ERROR:
            content += "internal_error";
            break;
    }

    if(!content.empty())
        content += ";" + extraContent;

    char* buffer = new char[configuration->getBufferSize()]();
    strcpy(buffer, content.c_str());
    buffer[content.length()] = '\0'; //test
    if(write(connectionSocketDescriptor, buffer, configuration->getBufferSize()) < 0) {
        std::cout << "Could not send response." << std::endl;
    }
    delete[] buffer;
}

std::string ServerSession::getRoomsForUser(User *user) {
    std::vector<Room*> rooms = roomRepository->findByUser(user);
    std::string roomsStr = "user_rooms";

    for(auto room : rooms) {
        roomsStr += ";" + room->getName();
    }

    return roomsStr;
}

std::string ServerSession::getAllRooms() {
    std::vector<Room*> rooms = roomRepository->findAll();
    std::string roomsStr = "all_rooms";

    for(auto room : rooms) {
        roomsStr += ";" + room->getName();
    }

    return roomsStr;
}

std::string ServerSession::getOnlineUsers(Room *room) {
    std::string users = "online_users;" + room->getName();
    for(User *user : *(room->getUsers())) {
        if(user->getStatus() != OFFLINE) {
            users += ";" + user->getName();

            if(user->getStatus() == AWAY) {
                users += "[AWAY]";
            }
        }
    }

    return users;
}
