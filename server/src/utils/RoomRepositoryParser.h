//
// Created by wiktor on 02.01.2021.
//

#ifndef STHLIKEIRCSERVER_ROOMREPOSITORYPARSER_H
#define STHLIKEIRCSERVER_ROOMREPOSITORYPARSER_H
#include "Parser.h"
#include "../repository/RoomRepository.h"

class RoomRepositoryParser : public Parser<RoomRepository> {
public:
    RoomRepository *parseFrom(std::string content) override;
    RoomRepository *parseFrom(std::ifstream &file) override;
    std::string parseTo(RoomRepository *object) override;
};


#endif //STHLIKEIRCSERVER_ROOMREPOSITORYPARSER_H
