#include "User.h"
#include <stdexcept>

int User::s8IdGenerator = 0;

User::User(const std::string& username, const std::string& password, UserProfile profile)
    : s8UserId(s8IdGenerator++), username(username), password(password), profile(profile)
{
    if(username.empty())
    {
        throw std::invalid_argument("Sorry, username cannot be empty. Think of a cool name!");
    }
    if(password.empty())
    {
        throw std::invalid_argument("Sorry, password cannot be empty. It is not secure for you!");
    }
}

User::User(int s8Id, const std::string& username, const std::string& password, UserProfile profile)
    : s8UserId(s8Id), username(username), password(password), profile(profile)
{
    if(username.empty())
    {
        throw std::invalid_argument("Sorry, username cannot be empty. Think of a cool name!");
    }
    if(password.empty())
    {
        throw std::invalid_argument("Sorry, password cannot be empty. It is not secure for you!");
    }
}

std::string        User::getUsername() const { return username; }
std::string        User::getPassword() const { return password; }
int                User::getId()       const { return s8UserId; }
const UserProfile& User::getProfile()  const { return profile; }
