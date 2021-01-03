#ifndef STHLIKEIRCSERVER_SERVERSESSION_H
#define STHLIKEIRCSERVER_SERVERSESSION_H
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <pthread.h>
#include <errno.h>
#include <iostream>
#include "../exceptions/ParsingError.h"
#include "../utils/UserRepositoryParser.h"
#include "../utils/RoomRepositoryParser.h"
#include "../exceptions/InitServerError.h"
#include "Configuration.h"
#include "../utils/MessageParser.h"
#include "../utils/ConfigurationParser.h"
#include "../repository/RoomRepository.h"
#include "../repository/UserRepository.h"

bool quit = false;
void quitSignalHandler(int signal);

class ServerSession {
private:
    Configuration* configuration;
    MessageParser* messageParser;
    RoomRepository* roomRepository;
    UserRepository* userRepository;
    pthread_mutex_t lock;
    pthread_cond_t con;
    int* sockets;
    int* currentThreads;
    void handleConnection(int connectionSocketDescriptor);
    int serverSocketDescriptor;
    int init();
    void initSignalHandler();
    void addThread(int connectionSocketDescriptor);
    static void* threadBehavior(void* tData);
public:
    ServerSession(std::ifstream &configFile, std::ifstream &usersFile, std::ifstream &roomsFile);
    ~ServerSession();
    void run();
    void sendMessage(User* user, Room* room);
    void sendServerMessage(User *user);
    void joinRoom(User* user, Room* room);
    void login(User* user, int connectionSocketDescriptor);
    User* createAccount(std::string name, std::string email, std::string password);
    Configuration *getConfiguration() const;
    void removeThread(int connectionSocketDescriptor);
    bool listenOnSocket(int connectionSocketDescriptor);
};

struct ThreadData
{
    int connectionSocketDescriptor;
    ServerSession* serverSession;
};

#endif //STHLIKEIRCSERVER_SERVERSESSION_H
