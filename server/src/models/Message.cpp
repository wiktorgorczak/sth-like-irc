//
// Created by wiktor on 28.12.2020.
//

#include "Message.h"

const std::string &Message::getContent() const {
    return content_;
}

void Message::setContent(const std::string &content) {
    content_ = content;
}

const User &Message::getUser() const {
    return user;
}

void Message::setUser(const User &user) {
    Message::user = user;
}

time_t Message::getTime() const {
    return time_;
}

void Message::setTime(time_t time) {
    time_ = time;
}

const Room &Message::getRoom() const {
    return room_;
}

void Message::setRoom(const Room &room) {
    room_ = room;
}
