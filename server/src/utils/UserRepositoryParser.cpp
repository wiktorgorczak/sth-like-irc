//User*
// Created by wiktor on 02.01.2021.
//

#include <iostream>
#include "UserRepositoryParser.h"

UserRepository *UserRepositoryParser::parseFrom(std::string content) {
    return nullptr;
}

UserRepository *UserRepositoryParser::parseFrom(std::ifstream &file) {
    auto repository = new UserRepository;

    while(file) {
        std::string name, email, password;

        auto user = new User;

        std::getline(file, name, ';');
        std::getline(file, email, ';');
        file >> password;
        file >> std::ws;

        if(!file)
            break;

        user->setName(name);
        user->setEmail(email);
        user->setPassword(password);
        user->setStatus(OFFLINE);
        user->setConnectionSocketDescriptor(-1);

        repository->add(user);
    }

    return repository;
}

std::string UserRepositoryParser::parseTo(UserRepository *object) {
    return std::string();
}
