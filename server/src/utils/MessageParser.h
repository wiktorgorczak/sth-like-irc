//
// Created by wiktor on 02.01.2021.
//

#ifndef STHLIKEIRCSERVER_MESSAGEPARSER_H
#define STHLIKEIRCSERVER_MESSAGEPARSER_H


#include "Parser.h"
#include "../models/Message.h"
#include "../repository/UserRepository.h"
#include "../repository/RoomRepository.h"

class MessageParser : public Parser<Message> {
private:
    RoomRepository* roomRepository;
    MessageType parseType(std::string type);
public:
    MessageParser(RoomRepository* roomRepository_);
    Message *parseFrom(std::string content) override;
    Message *parseFrom(std::ifstream &file) override;
    std::string parseTo(Message *object) override;
};


#endif //STHLIKEIRCSERVER_MESSAGEPARSER_H
