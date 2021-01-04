//
// Created by wiktor on 02.01.2021.
//

#ifndef STHLIKEIRCSERVER_USERREPOSITORY_H
#define STHLIKEIRCSERVER_USERREPOSITORY_H


#include "../models/User.h"
#include "Repository.h"

class UserRepository : public Repository<User> {
public:
    User* findByName(std::string name) override;
    User* findByEmail(std::string email);
    User* findBySocketDescriptor(int connectionSocketDescriptor);
};


#endif //STHLIKEIRCSERVER_USERREPOSITORY_H
