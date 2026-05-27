#pragma once
#include "User.h"

class Admin : public User {
private:
    std::string adminKey;
public:
    Admin(const std::string& username, const std::string& password,
        UserProfile profile, const std::string& adminKey);
    
    Admin(int id, const std::string& username, const std::string& password,
        UserProfile profile, const std::string& adminKey);

    const std::string& getAdminKey() const;
    void help() const override;
    ~Admin() override = default;
};