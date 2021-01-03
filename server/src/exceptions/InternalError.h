//
// Created by wiktor on 03.01.2021.
//

#ifndef STHLIKEIRCSERVER_INTERNALERROR_H
#define STHLIKEIRCSERVER_INTERNALERROR_H


#include <exception>

class InternalError : public std::exception {
public:
    const char *what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override;
};


#endif //STHLIKEIRCSERVER_INTERNALERROR_H
