#include "ServerSession.h"

ServerSession::ServerSession(std::ifstream &configFile, std::ifstream &usersFile, std::ifstream &roomsFile) {
    ConfigurationParser configurationParser;
    UserRepositoryParser userRepositoryParser;
    RoomRepositoryParser roomRepositoryParser;
    quit = false;
    messageParser = new MessageParser();
    currentThreads = new int;
    *currentThreads = 0;

    try {
        configuration = configurationParser.parseFrom(configFile);
        userRepository = userRepositoryParser.parseFrom(usersFile);
        roomRepository = roomRepositoryParser.parseFrom(roomsFile);
    } catch(ParsingError &exception) {
        std::cout << "Could not initialize server configuration due to parsing error." << std::endl;
        throw InitServerError();
    }

    sockets = new int[configuration->getMaxThreadCount()];

    for(int i = 0; i < configuration->getMaxThreadCount(); i++) {
        sockets[i] = -1;
    }

    initSignalHandler();
    serverSocketDescriptor = init();
}

void ServerSession::initSignalHandler() {
    struct sigaction sigIntHandler;
    sigIntHandler.sa_handler = quitSignalHandler;
    sigemptyset(&sigIntHandler.sa_mask);
    sigIntHandler.sa_flags = 0;
    sigaction(SIGINT, &sigIntHandler, NULL);
}

void quitSignalHandler(int signal) {
    quit = true;
}

int ServerSession::init() {
    std::cout << "Initializing server socket...";
    struct sockaddr_in serverAddress;
    char reuseAddrValue = 1;

    memset(&serverAddress, 0, sizeof(struct sockaddr));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serverAddress.sin_port = htons(configuration->getServerPort());

    int serverSocketDescriptor = socket(AF_INET, SOCK_STREAM, 0);
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
    struct ThreadData *tData = new ThreadData;
    tData->connectionSocketDescriptor = connectionSocketDescriptor;
    tData->serverSession = this;

    addThread(connectionSocketDescriptor);
    int createThreadResult = pthread_create(&thread, NULL, threadBehavior, (void*)tData);

    if(createThreadResult < 0) {
        std::cout << "Could not create thread for a connection!\t[ERROR]" << std::endl;
    }
}

bool ServerSession::listenOnSocket(int connectionSocketDescriptor) {

}

void* ServerSession::threadBehavior(void *tData) {
    pthread_detach(pthread_self());

    struct ThreadData* threadData = (struct ThreadData*)tData;
    int socket = threadData->connectionSocketDescriptor;
    ServerSession* serverSession = threadData->serverSession;
    char* buffer = new char[serverSession->getConfiguration()->getBufferSize()];

    while(serverSession->listenOnSocket(socket));

    serverSession->removeThread(socket);
    delete buffer;
    delete threadData;
    pthread_exit(NULL);
}

void ServerSession::run() {
    int connectionSocketDescriptor;

    while(!quit) {
        connectionSocketDescriptor = accept(serverSocketDescriptor, NULL, NULL);
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
