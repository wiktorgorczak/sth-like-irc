//
// Created by wiktor on 02.01.2021.
//

#ifndef STHLIKEIRCSERVER_INITSERVERERROR_H
#define STHLIKEIRCSERVER_INITSERVERERROR_H


#include <exception>

class InitServerError : public std::exception {
public:
    const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};


#endif //STHLIKEIRCSERVER_INITSERVERERROR_H
