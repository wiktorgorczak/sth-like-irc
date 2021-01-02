//
// Created by wiktor on 02.01.2021.
//

#include <iostream>
#include "ServerSession.h"
#include "../exceptions/ParsingError.h"
#include "../utils/UserRepositoryParser.h"
#include "../utils/RoomRepositoryParser.h"
#include "../exceptions/InitServerError.h"

ServerSession::ServerSession(std::ifstream &configFile, std::ifstream &usersFile, std::ifstream &roomsFile) {
    ConfigurationParser configurationParser;
    UserRepositoryParser userRepositoryParser;
    RoomRepositoryParser roomRepositoryParser;

    try {
        configuration = configurationParser.parseFrom(configFile);
        userRepository = userRepositoryParser.parseFrom(usersFile);
        roomRepository = roomRepositoryParser.parseFrom(roomsFile);
    } catch(ParsingError &exception) {
        std::cout << "Could not initialize server configuration due to parsing error." << std::endl;
        throw InitServerError();
    }

    messageParser = new MessageParser();
    currentThreads = new int;
    *currentThreads = 0;

}
