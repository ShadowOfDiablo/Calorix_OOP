#include "Trainee.h"
#include <iostream>

Trainee::Trainee(const std::string& username, const std::string& password,
    UserProfile profile)
    : User(username, password, profile) {
}
Trainee::Trainee(int id, const std::string& username, const std::string& password,
    UserProfile profile)
    : User(id, username, password, profile)
{
}

void Trainee::addFoodEntry(const FoodEntry& e) 
{ 
    foodDiary.push_back(e); 
}
void Trainee::addExerciseEntry(const ExerciseEntry& e) 
{ 
    exerciseDiary.push_back(e); 
}
void Trainee::addGoal(const FitnessGoal& g) 
{
    goals.push_back(g); 
}
void Trainee::addFavoriteExercise(const Exercise& ex) 
{ 
    favoriteExercises.push_back(ex); 
}

const std::vector<FoodEntry>& Trainee::getFoodDiary()         const
{ 
    return foodDiary; 
}
const std::vector<ExerciseEntry>& Trainee::getExerciseDiary()     const 
{ 
    return exerciseDiary; 
}
const std::vector<FitnessGoal>& Trainee::getGoals()             const
{ 
    return goals; 
}
const std::vector<Exercise>& Trainee::getFavoriteExercises() const 
{ 
    return favoriteExercises; 
}

void Trainee::help() const {
    std::cout << "Available commands (Trainee):\n"
        << "  log-food <food-name> <quantity_grams>\n"
        << "  log-exercise <exercise-name> <duration_minutes>\n"
        << "  view-daily-summary\n"
        << "  view-progress\n"
        << "  set-goals <goal-type> <target-value> <deadline>\n"
        << "  calculate-bmi\n"
        << "  calculate-bmr\n"
        << "  generate-workout-plan <duration_minutes>\n"
        << "  add-to-favorites <exercise-name>\n"
        << "  view-favorites\n"
        << "  logout\n";
}
