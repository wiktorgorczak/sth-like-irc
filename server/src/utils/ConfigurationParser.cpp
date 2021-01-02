//
// Created by wiktor on 02.01.2021.
//

#include "ConfigurationParser.h"

Configuration *ConfigurationParser::parseFrom(std::string content) {
    return Parser::parseFrom(content);
}

std::string ConfigurationParser::parseTo(Configuration *object) {
    return Parser::parseTo(object);
}

Configuration *ConfigurationParser::parseFrom(std::ifstream &file) {
    return nullptr;
}
