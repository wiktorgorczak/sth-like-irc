//
// Created by wiktor on 02.01.2021.
//

#ifndef STHLIKEIRCSERVER_REPOSITORY_H
#define STHLIKEIRCSERVER_REPOSITORY_H

#include <string>

template <typename T>
class Repository {
public:
    virtual void add(T* obj) = 0;
    virtual void remove(T* obj) = 0;
    virtual T* findByName(std::string name) = 0;
};


#endif //STHLIKEIRCSERVER_REPOSITORY_H
