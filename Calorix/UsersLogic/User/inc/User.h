#ifndef USER_H
#define USER_H

#include "UserProfile.h"
#include <string>

class User
{
private:
    int         s8UserId;
    std::string username;
    std::string password;
    UserProfile profile;

public:
    static int s8IdGenerator;

    User(const std::string& username, const std::string& password, UserProfile profile);
    User(int s8Id, const std::string& username, const std::string& password, UserProfile profile);

    std::string        getUsername() const;
    std::string        getPassword() const;
    int                getId()       const;
    const UserProfile& getProfile()  const;

    virtual ~User() = default;
    virtual void help() const = 0;
};

#endif // USER_H
