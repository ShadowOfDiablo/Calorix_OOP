#include "Admin.h"
#include "Calorix.h"
#include <iostream>
#include <unordered_map>

static MuscleGroup parseMuscleGroup(const std::string& s)
{
    static const std::unordered_map<std::string, MuscleGroup> table = {
        {"CHEST",     MuscleGroup::CHEST},
        {"BACK",      MuscleGroup::BACK},
        {"LEGS",      MuscleGroup::LEGS},
        {"SHOULDERS", MuscleGroup::SHOULDERS},
        {"ARMS",      MuscleGroup::ARMS},
        {"CORE",      MuscleGroup::CORE},
        {"CARDIO",    MuscleGroup::CARDIO},
    };
    auto it = table.find(s);
    if(it != table.end())
    {
        return it->second;
    }
    return MuscleGroup::CARDIO;
}

Admin::Admin(const std::string& username, const std::string& password,
             UserProfile profile, const std::string& adminKey)
    : User(username, password, profile), adminKey(adminKey)
{
}

Admin::Admin(int s8Id, const std::string& username, const std::string& password,
             UserProfile profile, const std::string& adminKey)
    : User(s8Id, username, password, profile), adminKey(adminKey)
{
}

const std::string& Admin::getAdminKey() const { return adminKey; }

void Admin::help() const
{
    std::cout << "Available commands (Admin):\n"
              << "  block-user <username>\n"
              << "  add-food <name> <calories> <protein> <carbs> <fat>\n"
              << "  add-exercise <name> <cal_per_hour> <muscle-group>\n"
              << "  update-food <food-name> <new-calories>\n"
              << "  logout\n";
}

void Admin::addFood(Calorix& system)
{
    std::string name;
    int s8Cal, s8Protein, s8Carbs, s8Fat;
    std::cout << "Enter name, calories/100g, protein/100g, carbs/100g, fat/100g:\n";
    std::cin >> name >> s8Cal >> s8Protein >> s8Carbs >> s8Fat;
    if(!system.addFood(name, s8Cal, s8Protein, s8Carbs, s8Fat))
    {
        std::cout << "Food '" << name << "' already exists.\n";
    }
}

void Admin::addExercise(Calorix& system)
{
    std::string name, groupStr;
    double f32CalPerHour;
    std::cout << "Enter name, calories/hour, muscle-group:\n";
    std::cin >> name >> f32CalPerHour >> groupStr;
    if(!system.addExercise(name, f32CalPerHour, parseMuscleGroup(groupStr)))
    {
        std::cout << "Exercise '" << name << "' already exists.\n";
    }
}

void Admin::updateFood(Calorix& system)
{
    std::string name;
    int s8NewCal;
    std::cout << "Enter food name and new calories/100g:\n";
    std::cin >> name >> s8NewCal;
    if(!system.updateFood(name, s8NewCal))
    {
        std::cout << "Food '" << name << "' not found.\n";
    }
}

void Admin::blockUser(const std::string& username, Calorix& system)
{
    if(!system.blockUser(username))
    {
        std::cout << "User '" << username << "' not found.\n";
        return;
    }
    std::cout << "User '" << username << "' blocked.\n";
}
