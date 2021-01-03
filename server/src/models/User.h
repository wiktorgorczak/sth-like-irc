#ifndef STHLIKEIRCSERVER_USER_H
#define STHLIKEIRCSERVER_USER_H
#include <string>
#include "UserStatus.h"

class User {
public:
    const std::string &getName() const;

    void setName(const std::string &name);

    const std::string &getEmail() const;

    void setEmail(const std::string &email);

    const std::string &getPassword() const;

    void setPassword(const std::string &password);

    UserStatus getStatus() const;

    void setStatus(UserStatus status);

    int getConnectionSocketDescriptor() const;

    void setConnectionSocketDescriptor(int connectionSocketDescriptor);

private:
    std::string name_;
    std::string email_;
    std::string password_;
    UserStatus status_;
    int connectionSocketDescriptor;
};


#endif //STHLIKEIRCSERVER_USER_H
