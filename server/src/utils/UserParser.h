//
// Created by wiktor on 03.01.2021.
//

#ifndef STHLIKEIRCSERVER_USERPARSER_H
#define STHLIKEIRCSERVER_USERPARSER_H

#include "../models/User.h"
#include "Parser.h"

class UserParser : public Parser<User> {
public:
    User *parseFrom(std::string content) override;

    User *parseFrom(std::ifstream &file) override;

    std::string parseTo(User *object) override;
};

#endif //STHLIKEIRCSERVER_USERPARSER_H
