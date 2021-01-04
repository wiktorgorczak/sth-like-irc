#ifndef STHLIKEIRCSERVER_SERVERSESSION_H
#define STHLIKEIRCSERVER_SERVERSESSION_H
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <csignal>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <pthread.h>
#include <cerrno>
#include <cctype>
#include <iostream>
#include <vector>
#include <algorithm>
#include "../exceptions/ParsingError.h"
#include "../utils/UserRepositoryParser.h"
#include "../utils/RoomRepositoryParser.h"
#include "../exceptions/InitServerError.h"
#include "Configuration.h"
#include "../utils/MessageParser.h"
#include "../utils/ConfigurationParser.h"
#include "../repository/RoomRepository.h"
#include "../repository/UserRepository.h"
#include "../utils/UserParser.h"
#include "../models/Response.h"

void quitSignalHandler(int signal);

class ServerSession {
private:
    Configuration* configuration;
    MessageParser* messageParser;
    RoomRepository* roomRepository;
    UserRepository* userRepository;
    UserParser* userParser;
    pthread_mutex_t lock;
    pthread_cond_t con;
    int* sockets;
    int* currentThreads;
    void handleConnection(int connectionSocketDescriptor);
    int serverSocketDescriptor;
    int init();
    static void initSignalHandler();
    void addThread(int connectionSocketDescriptor);
    void sendMessage(Message* message);
    void joinRoom(User* user, Room* room);
    void leaveRoom(User* user, Room* room);
    void login(User* user, int connectionSocketDescriptor);
    bool authorize(User* user);
    void createAccount(User* credentials);
    void setStatus(User* user, std::string statusStr);
    void logoff(User* user);
    static void* threadBehavior(void* tData);
    void sendResponse(Response response, int connectionSocketDescriptor);

public:
    ServerSession(std::ifstream &configFile, std::ifstream &usersFile, std::ifstream &roomsFile);
    ~ServerSession();
    void run();
    Configuration *getConfiguration() const;
    void removeThread(int connectionSocketDescriptor);
    bool listenOnSocket(int connectionSocketDescriptor, char buffer[], int bufferSize);

};

struct ThreadData {
    int connectionSocketDescriptor;
    ServerSession* serverSession;
};
#endif //STHLIKEIRCSERVER_SERVERSESSION_H
