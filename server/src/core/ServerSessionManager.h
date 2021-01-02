//
// Created by wiktor on 02.01.2021.
//

#ifndef STHLIKEIRCSERVER_SERVERSESSIONMANAGER_H
#define STHLIKEIRCSERVER_SERVERSESSIONMANAGER_H


#include <string>
#include "../models/User.h"
#include "ServerSession.h"

enum StatusCode {
    SUCCESS,
    INCORRECT_INPUT,
    ACCOUNT_EXISTS
};

class ServerSessionManager {
public:
    ServerSessionManager(std::ifstream configFile);
    User* createAccount(std::string login, std::string password);
    void startSession(User *user);
    void endSerssion(User *user);
    void sendServerMessage(std::string message, User *user);
    ~ServerSessionManager();
}

#endif //STHLIKEIRCSERVER_SERVERSESSIONMANAGER_H
