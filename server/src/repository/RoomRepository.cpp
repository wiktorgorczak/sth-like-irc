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