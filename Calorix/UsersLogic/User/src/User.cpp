#include "User.h"
#include <stdexcept>

int User::idGenerator = 0;

User::User(const std::string& username, const std::string& password, UserProfile profile)
	: userId(idGenerator++), username(username), password(password), profile(profile)
{
	if (username.empty()) {
		throw std::invalid_argument("Sorry, username cannot be empty. Think of a cool name!");
	}
	if (password.empty()) {
		throw std::invalid_argument("Sorry, password cannot be empty. It is not secure for you!");
	}
}

User::User(int id,
    const std::string& username,
    const std::string& password,
    UserProfile profile)
    : userId(id),
    username(username),
    password(password),
    profile(profile)
{
    if (username.empty()) {
        throw std::invalid_argument(
            "Sorry, username cannot be empty. Think of a cool name!");
    }

    if (password.empty()) {
        throw std::invalid_argument(
            "Sorry, password cannot be empty. It is not secure for you!");
    }
}
std::string User::getUsername() const
{
	return username;
}

std::string User::getPassword() const
{
	return password;
}

int User::getId() const {
	return userId;
}
