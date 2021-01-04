//
// Created by wiktor on 02.01.2021.
//

#include "ConfigurationParser.h"

Configuration *ConfigurationParser::parseFrom(std::string content) {
    return nullptr;
}

std::string ConfigurationParser::parseTo(Configuration *object) {
    return "";
}

Configuration *ConfigurationParser::parseFrom(std::ifstream &file) {
    auto configuration = new Configuration;

    configuration->setQueueSize(-1);
    configuration->setServerPort(-1);
    configuration->setMaxThreadCount(-1);
    configuration->setBufferSize(-1);

    while(file) {
        std::string line;

        getline(file, line, '=');

        int value;
        file >> value;
        file >> std::ws;

        if(!file)
            break;

        if(line == "maxthreadcount") {
            configuration->setMaxThreadCount(value);
        } else if(line == "serverport") {
            configuration->setServerPort(value);
        } else if(line == "queuesize") {
            configuration->setQueueSize(value);
        } else if(line == "buffersize") {
            configuration->setBufferSize(value);
        } else {
            throw ParsingError();
        }
    }

    if(!validate(configuration)) {
        throw ParsingError();
    }

    return configuration;
}

bool ConfigurationParser::validate(Configuration *configuration) {
    if(configuration->getBufferSize() < 0
        || configuration->getMaxThreadCount() < 0
        || configuration->getServerPort() < 0
        || configuration->getQueueSize() < 0) {
        return false;
    }
    return true;
}