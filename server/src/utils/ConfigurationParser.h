//
// Created by wiktor on 02.01.2021.
//

#ifndef STHLIKEIRCSERVER_CONFIGURATIONPARSER_H
#define STHLIKEIRCSERVER_CONFIGURATIONPARSER_H


#include "../core/Configuration.h"
#include "Parser.h"

class ConfigurationParser : public Parser<Configuration> {
private:
    static bool validate(Configuration* configuration);
public:
    Configuration *parseFrom(std::string content) override;
    Configuration *parseFrom(std::ifstream &file) override;
    std::string parseTo(Configuration *object) override;
};


#endif //STHLIKEIRCSERVER_CONFIGURATIONPARSER_H
