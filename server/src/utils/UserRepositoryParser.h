//
// Created by wiktor on 02.01.2021.
//

#ifndef STHLIKEIRCSERVER_USERREPOSITORYPARSER_H
#define STHLIKEIRCSERVER_USERREPOSITORYPARSER_H


#include "../repository/UserRepository.h"
#include "Parser.h"

class UserRepositoryParser : public Parser<UserRepository> {
public:
    UserRepository *parseFrom(std::string content) override;
    UserRepository *parseFrom(std::ifstream &file) override;
    std::string parseTo(UserRepository *object) override;
};


#endif //STHLIKEIRCSERVER_USERREPOSITORYPARSER_H
