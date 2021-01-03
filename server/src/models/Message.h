//
// Created by wiktor on 28.12.2020.
//

#ifndef STHLIKEIRCSERVER_MESSAGE_H
#define STHLIKEIRCSERVER_MESSAGE_H


#include <string>
#include <time.h>
#include "User.h"
#include "Room.h"
#include "MessageType.h"

class Message {
public:
    const std::string &getContent() const;

    void setContent(const std::string &content);

    User* getUser() const;

    void setUser(User* user);

    time_t getTime() const;

    void setTime(time_t time);

    Room* getRoom() const;

    void setRoom(Room* room);

    MessageType getType() const;

    void setType(MessageType type);

private:
    std::string content_;
    User* user;
    time_t time_;
    Room* room_;
    MessageType type_;
};


#endif //STHLIKEIRCSERVER_MESSAGE_H
