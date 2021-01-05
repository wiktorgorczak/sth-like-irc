//
// Created by wiktor on 02.01.2021.
//

#ifndef STHLIKEIRCSERVER_REPOSITORY_H
#define STHLIKEIRCSERVER_REPOSITORY_H

#include <string>
#include <vector>
#include <algorithm>

template <typename T>
class Repository {
protected:
    std::vector<T*>* objects;
public:
    Repository();
    ~Repository();
    virtual void add(T* obj);
    virtual void remove(T* obj);
    virtual T* findByName(std::string name) = 0;
    virtual std::vector<T*> findAll();
};

template<typename T>
Repository<T>::Repository() {
    objects = new std::vector<T*>;
}

template<typename T>
Repository<T>::~Repository() {
    delete objects;
}

template<typename T>
void Repository<T>::add(T *obj) {
    objects->push_back(obj);
}

template<typename T>
void Repository<T>::remove(T *obj) {
    objects->erase(std::remove(objects->begin(), objects->end(), obj), objects->end());
}

template<typename T>
std::vector<T*> Repository<T>::findAll() {
    std::vector<T*> all;

    for(auto obj : *objects) {
        all.push_back(obj);
    }

    return all;
}

#endif //STHLIKEIRCSERVER_REPOSITORY_H
