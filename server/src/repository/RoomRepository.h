//
// Created by wiktor on 02.01.2021.
//

#ifndef STHLIKEIRCSERVER_ROOMREPOSITORY_H
#define STHLIKEIRCSERVER_ROOMREPOSITORY_H


#include <vector>
#include "../models/Room.h"
#include "Repository.h"
#include "UserRepository.h"

class RoomRepository : public Repository<Room> {
public:
    Room* findByName(std::string name) override;
};


#endif //STHLIKEIRCSERVER_ROOMREPOSITORY_H
