#include "Calorix.h"

bool Calorix::registerTrainee(const std::string& username, const std::string& password,
    int s8Age, double f32Weight, double f32Height, Gender gender, ActivityLevel activityLevel)
{
    if(users.count(username) > 0)
    {
        return false;
    }
    UserProfile profile(s8Age, f32Weight, f32Height, gender, activityLevel);
    users[username] = std::make_unique<Trainee>(username, password, profile);
    return true;
}

bool Calorix::registerAdmin(const std::string& username, const std::string& password,
    const std::string& adminKey)
{
    if(users.count(username) > 0)
    {
        return false;
    }
    users[username] = std::make_unique<Admin>(username, password, UserProfile{}, adminKey);
    return true;
}

User* Calorix::login(const std::string& username, const std::string& password)
{
    auto it = users.find(username);
    if(it != users.end() && it->second->getPassword() == password)
    {
        return it->second.get();
    }
    return nullptr;
}

bool Calorix::addFood(const std::string& name, int s8Cal, int s8Protein, int s8Carbs, int s8Fat)
{
    if(foods.count(name) > 0)
    {
        return false;
    }
    foods.emplace(name, Food(name, s8Cal, s8Protein, s8Carbs, s8Fat));
    return true;
}

bool Calorix::addExercise(const std::string& name, double f32CalPerHour, MuscleGroup group)
{
    if(exercises.count(name) > 0)
    {
        return false;
    }
    exercises.emplace(name, Exercise(name, f32CalPerHour, group));
    return true;
}

bool Calorix::updateFood(const std::string& name, int s8NewCalories)
{
    auto it = foods.find(name);
    if(it == foods.end())
    {
        return false;
    }
    it->second.setCaloriesPer100g(s8NewCalories);
    return true;
}

bool Calorix::blockUser(const std::string& username)
{
    return users.erase(username) > 0;
}

Food* Calorix::findFood(const std::string& name)
{
    auto it = foods.find(name);
    if(it != foods.end())
    {
        return &it->second;
    }
    return nullptr;
}

Exercise* Calorix::findExercise(const std::string& name)
{
    auto it = exercises.find(name);
    if(it != exercises.end())
    {
        return &it->second;
    }
    return nullptr;
}
