//
// Created by wiktor on 02.01.2021.
//

#ifndef STHLIKEIRCSERVER_PARSER_H
#define STHLIKEIRCSERVER_PARSER_H

#include <string>
#include <iostream>
#include <fstream>
#include "../exceptions/ParsingError.h"

template <typename T>
class Parser {
public:
    virtual T* parseFrom(std::string content) = 0;
    virtual T* parseFrom(std::ifstream &file) = 0;
    virtual std::string parseTo(T* object) = 0;
};


#endif //STHLIKEIRCSERVER_PARSER_H
