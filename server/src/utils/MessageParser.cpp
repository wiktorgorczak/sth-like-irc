//
// Created by wiktor on 02.01.2021.
//

#include "MessageParser.h"

Message *MessageParser::parseFrom(std::string content) {
    std::string delimiter = ";";
    auto message = new Message;

    std::string username, password, roomName, type, messageText;
    size_t pos = 0;
    std::string tokens[4];

    for(std::string &token: tokens) {
        pos = content.find(delimiter);
        token = content.substr(0, pos);
        content.erase(0, pos + delimiter.length());

        if(token.empty()) {
            delete message;
            throw ParsingError();
        }
    }

    username = tokens[0];
    password = tokens[1];
    roomName = tokens[2];
    type = tokens[3];
    messageText = content;

    auto user = new User; //We create a temporary user
    // which will be replaced with the correct one during authorization.
    user->setName(username);
    user->setPassword(password);

    message->setUser(user);
    auto room = roomRepository->findByName(roomName);

    if(!room) {
        std::cerr << "There is no such room: " << roomName << std::endl;
        delete user;
        throw ParsingError();
    }

    message->setRoom(room);
    message->setType(parseType(type));
    message->setContent(messageText);

    time_t timeNow;
    time(&timeNow);
    message->setTime(timeNow);
    return message;
}

std::string MessageParser::parseTo(Message *object) {
    std::string parsed;

    time_t time_obj = object->getTime();
    char* time_arr = ctime(&time_obj);
    std::string time_str(time_arr);

    parsed += object->getUser()->getName() + ";";
    parsed += object->getRoom()->getName() + ";";
    parsed += time_str + ";";
    parsed += object->getContent();

    return parsed;
}

Message *MessageParser::parseFrom(std::ifstream &file) {
    return nullptr;
}

MessageParser::MessageParser(RoomRepository *roomRepository_)
    : Parser<Message>(), roomRepository(roomRepository_) {}

MessageType MessageParser::parseType(std::string type) {
    if(type == "create_account")
        return CREATE_ACCOUNT;
    else if(type == "join_room")
        return JOIN_ROOM;
    else if(type == "leave_room")
        return LEAVE_ROOM;
    else if(type == "login")
        return LOGIN;
    else if(type == "set_status")
        return SET_STATUS;
    else if(type == "logoff")
        return LOGOFF;
    else if(type == "get_rooms")
        return GET_ROOMS;
    else if(type == "get_rooms_for_user")
        return GET_ROOMS_FOR_USER;
    else
        return STANDARD;
}
