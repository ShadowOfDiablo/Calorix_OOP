#pragma once
#include "User.h"

class Calorix;

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

    void addFood(Calorix& system);
    void addExercise(Calorix& system);
    void updateFood(Calorix& system);
    void blockUser(const std::string& username, Calorix& system);
};