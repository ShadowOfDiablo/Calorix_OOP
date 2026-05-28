#pragma once
#include <memory>
#include <unordered_map>
#include "User.h"
#include "Trainee.h"
#include "Admin.h"
#include "Food.h"
#include "Exercise.h"

class Calorix {
    std::unordered_map<std::string, std::unique_ptr<User>> users;
    std::unordered_map<std::string, Food>                  foods;
    std::unordered_map<std::string, Exercise>              exercises;

public:
    bool registerTrainee(
        const std::string& username,
        const std::string& password,
        int age,
        double weight,
        double height,
        Gender gender,
        ActivityLevel activityLevel
    );

    bool registerAdmin(
        const std::string& username,
        const std::string& password,
        const std::string& adminKey
    );

    User* login(const std::string& username, const std::string& password);

    bool addFood(const std::string& name, int cal, int protein, int carbs, int fat);
    bool addExercise(const std::string& name, double calPerHour, MuscleGroup group);
    bool updateFood(const std::string& name, int newCalories);
    bool blockUser(const std::string& username);

    Food*     findFood(const std::string& name);
    Exercise* findExercise(const std::string& name);
};
