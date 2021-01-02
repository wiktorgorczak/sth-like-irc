//
// Created by wiktor on 02.01.2021.
//

#ifndef STHLIKEIRCSERVER_SERVERSESSION_H
#define STHLIKEIRCSERVER_SERVERSESSION_H
#include <pthread.h>
#include "Configuration.h"
#include "../utils/MessageParser.h"
#include "../utils/ConfigurationParser.h"
#include "../repository/RoomRepository.h"
#include "../repository/UserRepository.h"

class ServerSession {
private:
    Configuration* configuration;
    MessageParser* messageParser;
//    ConfigurationParser* configurationParser;
    RoomRepository* roomRepository;
    UserRepository* userRepository;
//    const int maxThreadCount;
    pthread_mutex_t lock;
    pthread_cond_t con;
    int* sockets;
    int* currentThreads;
    void* threadBehavior(void* t_data);
    void handleConnection(int connectionSocketDescriptor);

public:
    ServerSession(std::ifstream &configFile, std::ifstream &usersFile, std::ifstream &roomsFile);
    ~ServerSession();
    void run();
};


#endif //STHLIKEIRCSERVER_SERVERSESSION_H
