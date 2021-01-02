//
// Created by wiktor on 28.12.2020.
//

#ifndef STHLIKEIRCSERVER_MESSAGE_H
#define STHLIKEIRCSERVER_MESSAGE_H


#include <string>
#include <time.h>
#include "User.h"
#include "Room.h"

class Message {
public:
    const std::string &getContent() const;

    void setContent(const std::string &content);

    const User &getUser() const;

    void setUser(const User &user);

    time_t getTime() const;

    void setTime(time_t time);

    const Room &getRoom() const;

    void setRoom(const Room &room);

private:
    std::string content_;
    User user;
    time_t time_;
    Room room_;
};


#endif //STHLIKEIRCSERVER_MESSAGE_H
