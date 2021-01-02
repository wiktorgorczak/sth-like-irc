//
// Created by wiktor on 02.01.2021.
//

#ifndef STHLIKEIRCSERVER_PARSINGERROR_H
#define STHLIKEIRCSERVER_PARSINGERROR_H


#include <exception>

class ParsingError : public std::exception {
public:
    const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};


#endif //STHLIKEIRCSERVER_PARSINGERROR_H
