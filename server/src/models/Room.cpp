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

std::vector<User*>* Room::getUsers() {
    return &users_;
}

void Room::setUsers(const std::vector<User*> &users) {
    users_ = users;
}

void Room::addUser(User *user) {
    for(auto currentUser : users_) {
        if(currentUser == user)
            return;
    }
    users_.push_back(user);
}
