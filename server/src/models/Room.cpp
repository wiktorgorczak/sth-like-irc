//
// Created by wiktor on 28.12.2020.
//

#include "Room.h"

const std::string &Room::getName() const {
    return name_;
}

void Room::setName(const std::string &name) {
    name_ = name;
}

const std::vector<User> &Room::getUsers() const {
    return users_;
}

void Room::setUsers(const std::vector<User> &users) {
    users_ = users;
}
