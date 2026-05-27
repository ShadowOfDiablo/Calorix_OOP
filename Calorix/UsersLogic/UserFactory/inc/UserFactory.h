#pragma once
#include <memory>
#include "User.h"
#include "Trainee.h"
#include "Admin.h"

class UserFactory {
public:
    static std::unique_ptr<User> createTrainee(
        int id,
        const std::string& username,
        const std::string& password,
        int age,
        double weight,
        double height,
        Gender gender,
        ActivityLevel activityLevel
    );

    static std::unique_ptr<User> createAdmin(
        int id,
        const std::string& username,
        const std::string& password,
        const std::string& adminKey
    );
};
