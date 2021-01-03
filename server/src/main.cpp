#include <iostream>
#include <fstream>
#include "core/ServerSession.h"

#define CONFIGURATION_FILE "config.ini"
#define USERS_FILE "users.ini"
#define ROOMS_FILE "rooms.ini"

int main()
{
    std::cout << "Starting SthLikeIrc server..." << std::endl;
    std::cout << "Opening config.ini\t";

    std::ifstream configFile(CONFIGURATION_FILE);

    if(configFile.good()) {
        std::cout << "[OK]" << std::endl;
    }

    std::cout << "Opening users.ini\t";

    std::ifstream usersFile(USERS_FILE);

    if(usersFile.good()) {
        std::cout << "[OK]" << std::endl;
    }

    std::cout << "Opening rooms.ini\t";
    std::ifstream roomsFile(ROOMS_FILE);

    if(roomsFile.good()) {
        std::cout << "[OK]" << std::endl;
    }

    auto *serverSession = new ServerSession(configFile, usersFile, roomsFile);
    serverSession->run();
    delete serverSession;

    return 0;
}