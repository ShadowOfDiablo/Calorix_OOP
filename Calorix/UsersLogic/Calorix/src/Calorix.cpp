#include "Calorix.h"

// void UserFactory::add_user(std::unique_ptr<User> user_ptr,int id)
// {
//     std::pair<int,std::unique_ptr<User>> pair;
//     pair.first = id;
//     pair.second = std::move(user_ptr);
//     st.insert(pair);
// }
bool Calorix::registerTrainee(const std::string& username,const std::string& password,int age,double weight,double height,Gender gender,ActivityLevel activityLevel)
{
    if(users.count(username) > 0)
    {
        return false;
    }
    UserProfile profile(age,weight,height,gender,activityLevel);
    users[username] = std::make_unique<Trainee>(username,password,profile);
    return true;
}

User* Calorix::login(const std::string& username, const std::string& password)
{
    std::unordered_map<std::string,std::unique_ptr<User>>::iterator it = users.find(username);
    if(it != users.end() && it->second->getPassword() == password)
    {
        return it->second.get();
    }
    return nullptr;
}
bool Calorix::registerAdmin(const std::string& username, const std::string& password, const std::string& adminKey)
{
    if(users.count(username) > 0)
    {
        return false;
    }
    users[username] = std::make_unique<Admin>(username, password, UserProfile{}, adminKey);
    return true;
}

bool Calorix::addFood(const std::string& name, int cal, int protein, int carbs, int fat)
{
    if(foods.count(name) > 0)
    {
        return false;
    }
    foods.emplace(name, Food(name, cal, protein, carbs, fat));
    return true;
}

bool Calorix::addExercise(const std::string& name, double calPerHour, MuscleGroup group)
{
    if(exercises.count(name) > 0)
    {
        return false;
    }
    exercises.emplace(name, Exercise(name, calPerHour, group));
    return true;
}

bool Calorix::updateFood(const std::string& name, int newCalories)
{
    auto it = foods.find(name);
    if(it == foods.end())
    {
        return false;
    }
    it->second.setCaloriesPer100g(newCalories);
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
