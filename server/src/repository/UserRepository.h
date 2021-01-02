//
// Created by wiktor on 02.01.2021.
//

#ifndef STHLIKEIRCSERVER_USERREPOSITORY_H
#define STHLIKEIRCSERVER_USERREPOSITORY_H


#include <vector>
#include "../models/User.h"
#include "Repository.h"

class UserRepository : public Repository<User> {
private:
    std::vector<User*>* users;

public:
    UserRepository();
    ~UserRepository();
    void add(User* user) override;
    void remove(User* user) override;
    User* findByName(std::string name) override;
    User* findByEmail(std::string email);
};


#endif //STHLIKEIRCSERVER_USERREPOSITORY_H
