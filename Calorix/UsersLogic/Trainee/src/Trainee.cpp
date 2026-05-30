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

void Trainee::addToFavorites(Calorix& system)
{
    std::string name;
    std::cout << "Enter exercise name:\n";
    std::cin >> name;
    Exercise* exercise = system.findExercise(name);
    if(!exercise)
    {
        std::cout << "Exercise '" << name << "' not found.\n";
        return;
    }
    addFavoriteExercise(*exercise);
    std::cout << name << " added to favorites.\n";
}

void Trainee::viewFavorites() const
{
    if(favoriteExercises.empty())
    {
        std::cout << "No favorite exercises saved.\n";
        return;
    }
    std::cout << "--- Favorite exercises ---\n";
    for(const auto& ex : favoriteExercises)
    {
        std::cout << ex.getName() << "  |  " << ex.getCaloriesBurnedPerHour() << " kcal/h\n";
    }
}

void Trainee::calculateBMI() const
{
    double weight = getProfile().getWeight();
    double height = getProfile().getHeight();
    double bmi = weight / (height * height);

    std::string category;
    if(bmi < 18.5)
        category = "Underweight";
    else if(bmi < 25.0)
        category = "Normal weight";
    else if(bmi < 30.0)
        category = "Overweight";
    else
        category = "Obese";

    std::cout << "BMI: " << bmi << "  (" << category << ")\n";
}

void Trainee::calculateBMR() const
{
    // Harris-Benedict equation constants
    constexpr double MALE_BASE        = 88.362;
    constexpr double MALE_WEIGHT_COEF = 13.397;
    constexpr double MALE_HEIGHT_COEF =  4.799;
    constexpr double MALE_AGE_COEF    =  5.677;

    constexpr double FEMALE_BASE        = 447.593;
    constexpr double FEMALE_WEIGHT_COEF =   9.247;
    constexpr double FEMALE_HEIGHT_COEF =   3.098;
    constexpr double FEMALE_AGE_COEF    =   4.330;

    double weight    = getProfile().getWeight();
    double heightCm  = getProfile().getHeight() * 100.0;
    int    age       = getProfile().getAge();
    Gender gender    = getProfile().getGender();

    double bmr;
    if(gender == Gender::MALE)
    {
        bmr = MALE_BASE + (MALE_WEIGHT_COEF * weight) + (MALE_HEIGHT_COEF * heightCm) - (MALE_AGE_COEF * age);
    }
    else if(gender == Gender::FEMALE)
    {
        bmr = FEMALE_BASE + (FEMALE_WEIGHT_COEF * weight) + (FEMALE_HEIGHT_COEF * heightCm) - (FEMALE_AGE_COEF * age);
    }
    else
    {
        double male   = MALE_BASE   + (MALE_WEIGHT_COEF   * weight) + (MALE_HEIGHT_COEF   * heightCm) - (MALE_AGE_COEF   * age);
        double female = FEMALE_BASE + (FEMALE_WEIGHT_COEF * weight) + (FEMALE_HEIGHT_COEF * heightCm) - (FEMALE_AGE_COEF * age);
        bmr = (male + female) / 2.0;
    }

    std::cout << "BMR: " << bmr << " kcal/day (calories needed at complete rest)\n";
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
