#include <iostream>
#include <fstream>
#include "core/ServerSession.h"
#include <unistd.h>
#define CONFIGURATION_FILE "config.ini"
#define USERS_FILE "users.ini"
#define ROOMS_FILE "rooms.ini"
std::string get_current_dir() {
    char buff[10000]; //create string buffer to hold path
    getcwd( buff, 10000 );
    std::string current_working_dir(buff);
    return current_working_dir;
}
int main()
{
    std::cout << "Starting SthLikeIrc server..." << std::endl;
    std::cout << "Working directory: " << get_current_dir() << std::endl;

    std::cout << "Opening config.ini\t";

    std::ifstream configFile(CONFIGURATION_FILE);

    if(configFile.good()) {
        std::cout << "[OK]" << std::endl;
    } else {
        std::cout << "[ERROR]" << std::endl;
        return EXIT_FAILURE;
    }

    std::cout << "Opening users.ini\t";

    std::ifstream usersFile(USERS_FILE);

    if(usersFile.good()) {
        std::cout << "[OK]" << std::endl;
    } else {
        std::cout << "[ERROR]" << std::endl;
        return EXIT_FAILURE;
    }
    std::cout << "Opening rooms.ini\t";

    std::ifstream roomsFile(ROOMS_FILE);

    if(roomsFile.good()) {
        std::cout << "[OK]" << std::endl;
    } else {
        std::cout << "[ERROR]" << std::endl;
        return EXIT_FAILURE;
    }

    auto *serverSession = new ServerSession(configFile, usersFile, roomsFile);
    serverSession->run();
    delete serverSession;

    return 0;
}