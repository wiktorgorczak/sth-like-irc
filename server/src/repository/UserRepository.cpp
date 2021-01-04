//
// Created by wiktor on 02.01.2021.
//

#include "UserRepository.h"

User *UserRepository::findByName(std::string name) {
    for(auto user : *objects) {
        if(user->getName() == name)
            return user;
    }
    return nullptr;
}

User *UserRepository::findByEmail(std::string email) {
    return nullptr;
}

User *UserRepository::findBySocketDescriptor(int connectionSocketDescriptor) {
    return nullptr;
}
