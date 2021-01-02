//
// Created by wiktor on 02.01.2021.
//

#include "MessageParser.h"

Message *MessageParser::parseFrom(std::string content) {
    return Parser::parseFrom(content);
}

std::string MessageParser::parseTo(Message *object) {
    return Parser::parseTo(object);
}

Message *MessageParser::parseFrom(std::ifstream &file) {
    return nullptr;
}
