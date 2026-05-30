#include "Trainee.h"
#include "Calorix.h"
#include <iostream>

Trainee::Trainee(const std::string& username, const std::string& password, UserProfile profile)
    : User(username, password, profile)
{
}

Trainee::Trainee(int s8Id, const std::string& username, const std::string& password, UserProfile profile)
    : User(s8Id, username, password, profile)
{
}

void Trainee::addFoodEntry(const FoodEntry& entry)         { foodDiary.push_back(entry); }
void Trainee::addExerciseEntry(const ExerciseEntry& entry) { exerciseDiary.push_back(entry); }
void Trainee::addGoal(const FitnessGoal& goal)             { goals.push_back(goal); }
void Trainee::addFavoriteExercise(const Exercise& ex)      { favoriteExercises.push_back(ex); }

const std::vector<FoodEntry>&     Trainee::getFoodDiary()         const { return foodDiary; }
const std::vector<ExerciseEntry>& Trainee::getExerciseDiary()     const { return exerciseDiary; }
const std::vector<FitnessGoal>&   Trainee::getGoals()             const { return goals; }
const std::vector<Exercise>&      Trainee::getFavoriteExercises() const { return favoriteExercises; }

void Trainee::logFood(Calorix& system)
{
    std::string name;
    double f32Grams;
    std::cout << "Enter food name and quantity (grams):\n";
    std::cin >> name >> f32Grams;
    Food* p_food = system.findFood(name);
    if(!p_food)
    {
        std::cout << "Food '" << name << "' not found.\n";
        return;
    }
    addFoodEntry(FoodEntry(*p_food, f32Grams, Date::today()));
    std::cout << "Logged " << f32Grams << "g of " << name << ".\n";
}

void Trainee::logExercise(Calorix& system)
{
    std::string name;
    int s8Minutes;
    std::cout << "Enter exercise name and duration (minutes):\n";
    std::cin >> name >> s8Minutes;
    Exercise* p_exercise = system.findExercise(name);
    if(!p_exercise)
    {
        std::cout << "Exercise '" << name << "' not found.\n";
        return;
    }
    addExerciseEntry(ExerciseEntry(*p_exercise, s8Minutes, Date::today()));
    std::cout << "Logged " << s8Minutes << " minutes of " << name << ".\n";
}

void Trainee::viewDailySummary() const
{
    Date today = Date::today();
    double f32TotalCal = 0, f32TotalProtein = 0, f32TotalCarbs = 0, f32TotalFat = 0;

    std::cout << "--- Food today ---\n";
    for(const auto& entry : foodDiary)
    {
        if(entry.getDate() == today)
        {
            double f32Cal = entry.calculateCalories();
            std::cout << entry.getFood().getName() << "  " << entry.getQuantityGrams()
                      << "g  |  " << f32Cal << " kcal\n";
            f32TotalCal     += f32Cal;
            f32TotalProtein += entry.calculateProtein();
            f32TotalCarbs   += entry.calculateCarbs();
            f32TotalFat     += entry.calculateFat();
        }
    }
    std::cout << "Total intake:  " << f32TotalCal << " kcal  |  protein " << f32TotalProtein
              << "g  |  carbs " << f32TotalCarbs << "g  |  fat " << f32TotalFat << "g\n\n";

    double f32TotalBurned = 0;
    std::cout << "--- Exercise today ---\n";
    for(const auto& entry : exerciseDiary)
    {
        if(entry.getDate() == today)
        {
            double f32Burned = entry.calculateBurnedCalories();
            std::cout << entry.getExercise().getName() << "  " << entry.getDurationMinutes()
                      << " min  |  " << f32Burned << " kcal burned\n";
            f32TotalBurned += f32Burned;
        }
    }
    std::cout << "Total burned:  " << f32TotalBurned << " kcal\n";
    std::cout << "Net calories:  " << f32TotalCal - f32TotalBurned << " kcal\n";
}

void Trainee::viewProgress() const
{
    double f32CurrentWeight = getProfile().getWeight();
    std::cout << "Current weight: " << f32CurrentWeight << " kg\n";

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
            case GoalType::WEIGHT_LOSS:  typeStr = "Weight loss";  break;
            case GoalType::BULKING:      typeStr = "Bulking";      break;
            case GoalType::MAINTENANCE:  typeStr = "Maintenance";  break;
        }
        double f32Target = goal.getTargetValue();
        double f32Diff   = f32CurrentWeight - f32Target;
        std::cout << typeStr << "  |  target " << f32Target << " kg"
                  << "  |  deadline " << goal.getDeadline().toString()
                  << "  |  ";
        if(goal.getIsAchieved())
        {
            std::cout << "ACHIEVED\n";
        }
        else
        {
            std::cout << (f32Diff > 0 ? f32Diff : -f32Diff) << " kg "
                      << (f32Diff > 0 ? "to lose" : "to gain") << "\n";
        }
    }
}

void Trainee::addToFavorites(Calorix& system)
{
    std::string name;
    std::cout << "Enter exercise name:\n";
    std::cin >> name;
    Exercise* p_exercise = system.findExercise(name);
    if(!p_exercise)
    {
        std::cout << "Exercise '" << name << "' not found.\n";
        return;
    }
    addFavoriteExercise(*p_exercise);
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
    double f32Weight = getProfile().getWeight();
    double f32Height = getProfile().getHeight();
    double f32Bmi    = f32Weight / (f32Height * f32Height);

    std::string category;
    if(f32Bmi < 18.5)
        category = "Underweight";
    else if(f32Bmi < 25.0)
        category = "Normal weight";
    else if(f32Bmi < 30.0)
        category = "Overweight";
    else
        category = "Obese";

    std::cout << "BMI: " << f32Bmi << "  (" << category << ")\n";
}

void Trainee::calculateBMR() const
{
    constexpr double MALE_BASE          = 88.362;
    constexpr double MALE_WEIGHT_COEF   = 13.397;
    constexpr double MALE_HEIGHT_COEF   =  4.799;
    constexpr double MALE_AGE_COEF      =  5.677;

    constexpr double FEMALE_BASE        = 447.593;
    constexpr double FEMALE_WEIGHT_COEF =   9.247;
    constexpr double FEMALE_HEIGHT_COEF =   3.098;
    constexpr double FEMALE_AGE_COEF    =   4.330;

    double f32Weight   = getProfile().getWeight();
    double f32HeightCm = getProfile().getHeight() * 100.0;
    int    s8Age       = getProfile().getAge();
    Gender gender      = getProfile().getGender();

    double f32Bmr;
    if(gender == Gender::MALE)
    {
        f32Bmr = MALE_BASE + (MALE_WEIGHT_COEF * f32Weight) + (MALE_HEIGHT_COEF * f32HeightCm) - (MALE_AGE_COEF * s8Age);
    }
    else if(gender == Gender::FEMALE)
    {
        f32Bmr = FEMALE_BASE + (FEMALE_WEIGHT_COEF * f32Weight) + (FEMALE_HEIGHT_COEF * f32HeightCm) - (FEMALE_AGE_COEF * s8Age);
    }
    else
    {
        double f32Male   = MALE_BASE   + (MALE_WEIGHT_COEF   * f32Weight) + (MALE_HEIGHT_COEF   * f32HeightCm) - (MALE_AGE_COEF   * s8Age);
        double f32Female = FEMALE_BASE + (FEMALE_WEIGHT_COEF * f32Weight) + (FEMALE_HEIGHT_COEF * f32HeightCm) - (FEMALE_AGE_COEF * s8Age);
        f32Bmr = (f32Male + f32Female) / 2.0;
    }

    std::cout << "BMR: " << f32Bmr << " kcal/day (calories needed at complete rest)\n";
}

void Trainee::help() const
{
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
