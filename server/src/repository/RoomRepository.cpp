//
// Created by wiktor on 02.01.2021.
//

#include "RoomRepository.h"

Room *RoomRepository::findByName(std::string name) {
    for(auto obj : *objects) {
        if(obj->getName() == name)
            return obj;
    }
    return nullptr;
}

std::vector<Room *> RoomRepository::findByUser(User *user) {
    std::vector<Room*> rooms;
    for(auto obj : *objects) {
        std::vector<User*>* users = obj->getUsers();

        for(auto roomUser : *users) {
            if(roomUser == user) {
                rooms.push_back(obj);
                break;
            }
        }
    }

    return rooms;
}
