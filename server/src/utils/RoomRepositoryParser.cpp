//
// Created by wiktor on 02.01.2021.
//

#include "RoomRepositoryParser.h"

RoomRepository *RoomRepositoryParser::parseFrom(std::string content) {
    return nullptr;
}

RoomRepository *RoomRepositoryParser::parseFrom(std::ifstream &file) {
    auto repository = new RoomRepository;

    while(file) {
        auto room = new Room;
        std::string name;
        std::string username;

        std::getline(file, name, '\n');
        room->setName(name);

        std::getline(file, username, '\n');
        while(username != "END" && !username.empty()) {
            auto user = userRepository->findByName(username);

            if(user) {
                room->addUser(user);
            } else {
                std::cerr << "No such user: " << username << std::endl;
            }
            std::getline(file, username, '\n');
        }

        file >> std::ws;

        repository->add(room);
    }

    return repository;
}

std::string RoomRepositoryParser::parseTo(RoomRepository *object) {
    return std::string();
}

RoomRepositoryParser::RoomRepositoryParser(UserRepository *userRepository_)
: Parser<RoomRepository>(), userRepository(userRepository_) {
}
