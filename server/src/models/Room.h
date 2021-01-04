//
// Created by wiktor on 28.12.2020.
//

#ifndef STHLIKEIRCSERVER_ROOM_H
#define STHLIKEIRCSERVER_ROOM_H

#include <string>
#include <vector>
#include "User.h"

class Room {
public:
    const std::string &getName() const;

    void setName(const std::string &name);

    std::vector<User*>* getUsers();

    void setUsers(const std::vector<User*> &users);

    void addUser(User* user);
private:
    std::string name_;
    std::vector<User*> users_;
};


#endif //STHLIKEIRCSERVER_ROOM_H
