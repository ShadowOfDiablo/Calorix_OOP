#include "Trainee.h"
#include "Calorix.h"
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

void Trainee::logFood(Calorix& system)
{
    std::string name;
    double grams;
    std::cout << "Enter food name and quantity (grams):\n";
    std::cin >> name >> grams;
    Food* food = system.findFood(name);
    if(!food)
    {
        std::cout << "Food '" << name << "' not found.\n";
        return;
    }
    addFoodEntry(FoodEntry(*food, grams, Date::today()));
    std::cout << "Logged " << grams << "g of " << name << ".\n";
}

void Trainee::logExercise(Calorix& system)
{
    std::string name;
    int minutes;
    std::cout << "Enter exercise name and duration (minutes):\n";
    std::cin >> name >> minutes;
    Exercise* exercise = system.findExercise(name);
    if(!exercise)
    {
        std::cout << "Exercise '" << name << "' not found.\n";
        return;
    }
    addExerciseEntry(ExerciseEntry(*exercise, minutes, Date::today()));
    std::cout << "Logged " << minutes << " minutes of " << name << ".\n";
}

void Trainee::viewDailySummary() const
{
    Date today = Date::today();
    double totalCal = 0, totalProtein = 0, totalCarbs = 0, totalFat = 0;

    std::cout << "--- Food today ---\n";
    for(const auto& entry : foodDiary)
    {
        if(entry.getDate() == today)
        {
            double cal = entry.calculateCalories();
            std::cout << entry.getFood().getName() << "  " << entry.getQuantityGrams()
                      << "g  |  " << cal << " kcal\n";
            totalCal     += cal;
            totalProtein += entry.calculateProtein();
            totalCarbs   += entry.calculateCarbs();
            totalFat     += entry.calculateFat();
        }
    }
    std::cout << "Total intake:  " << totalCal << " kcal  |  protein " << totalProtein
              << "g  |  carbs " << totalCarbs << "g  |  fat " << totalFat << "g\n\n";

    double totalBurned = 0;
    std::cout << "--- Exercise today ---\n";
    for(const auto& entry : exerciseDiary)
    {
        if(entry.getDate() == today)
        {
            double burned = entry.calculateBurnedCalories();
            std::cout << entry.getExercise().getName() << "  " << entry.getDurationMinutes()
                      << " min  |  " << burned << " kcal burned\n";
            totalBurned += burned;
        }
    }
    std::cout << "Total burned:  " << totalBurned << " kcal\n";
    std::cout << "Net calories:  " << totalCal - totalBurned << " kcal\n";
}

void Trainee::viewProgress() const
{
    double currentWeight = getProfile().getWeight();
    std::cout << "Current weight: " << currentWeight << " kg\n";

    if(goals.empty())
    {
        std::cout << "No goals set.\n";
        return;
    }

    std::cout << "--- Goals ---\n";
    for(const auto& goal : goals)
    {
        std::string typeStr;
        switch(goal.getGoalType())
        {
            case GoalType::WEIGHT_LOSS:   typeStr = "Weight loss";   break;
            case GoalType::BULKING:       typeStr = "Bulking";       break;
            case GoalType::MAINTENANCE:   typeStr = "Maintenance";   break;
        }
        double target = goal.getTargetValue();
        double diff   = currentWeight - target;
        std::cout << typeStr << "  |  target " << target << " kg"
                  << "  |  deadline " << goal.getDeadline().toString()
                  << "  |  ";
        if(goal.getIsAchieved())
        {
            std::cout << "ACHIEVED\n";
        }
        else
        {
            std::cout << (diff > 0 ? diff : -diff) << " kg "
                      << (diff > 0 ? "to lose" : "to gain") << "\n";
        }
    }
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
