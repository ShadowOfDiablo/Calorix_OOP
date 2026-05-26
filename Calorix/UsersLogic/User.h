#pragma once
#include "UserProfile.h"
#include <string>
class User {
private:
	int userId;
	std::string username;
	std::string password;
	UserProfile profile;
public:
	static int idGenerator;
	User(const std::string& username, const std::string& password, UserProfile profile);
	User(int id, const std::string& username, const std::string& password, UserProfile profile);
	std::string getUsername() const;
	std::string getPassword() const;
	int getId() const;

	virtual ~User() = default;
	virtual void help() const = 0;
};