#include "User.h"

const std::string &User::getName() const {
    return name_;
}

void User::setName(const std::string &name) {
    name_ = name;
}

const std::string &User::getEmail() const {
    return email_;
}

void User::setEmail(const std::string &email) {
    email_ = email;
}

const std::string &User::getPassword() const {
    return password_;
}

void User::setPassword(const std::string &password) {
    password_ = password;
}

UserStatus User::getStatus() const {
    return status_;
}

void User::setStatus(UserStatus status) {
    status_ = status;
}
