#ifndef CALORIX_H
#define CALORIX_H

#include <memory>
#include <unordered_map>
#include "User.h"
#include "Trainee.h"
#include "Admin.h"
#include "Food.h"
#include "Exercise.h"

class FileManager;

class Calorix
{
    friend class FileManager;

    std::unordered_map<std::string, std::unique_ptr<User>> users;
    std::unordered_map<std::string, Food>                  foods;
    std::unordered_map<std::string, Exercise>              exercises;

public:
    bool registerTrainee(
        const std::string& username,
        const std::string& password,
        int s8Age,
        double f32Weight,
        double f32Height,
        Gender gender,
        ActivityLevel activityLevel
    );

    bool registerAdmin(
        const std::string& username,
        const std::string& password,
        const std::string& adminKey
    );

    User* login(const std::string& username, const std::string& password);

    bool addFood(const std::string& name, int s8Cal, int s8Protein, int s8Carbs, int s8Fat);
    bool addExercise(const std::string& name, double f32CalPerHour, MuscleGroup group);
    bool updateFood(const std::string& name, int s8NewCalories);
    bool blockUser(const std::string& username);

    Food*     findFood(const std::string& name);
    Exercise* findExercise(const std::string& name);

    const std::unordered_map<std::string, Food>&                  getFoods()     const;
    const std::unordered_map<std::string, Exercise>&              getExercises() const;
    const std::unordered_map<std::string, std::unique_ptr<User>>& getUsers()     const;
};

#endif // CALORIX_H
