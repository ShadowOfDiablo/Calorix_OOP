#pragma once
#include "User.h"
#include "FoodEntries.h"
#include "ExerciseEntries.h"
#include "FitnessGoal.h"
#include "Exercise.h"
#include <vector>

class Calorix;

class Trainee : public User {
private:
    std::vector<FoodEntry>     foodDiary;
    std::vector<ExerciseEntry> exerciseDiary;
    std::vector<FitnessGoal>   goals;
    std::vector<Exercise>      favoriteExercises;
public:
    Trainee(const std::string& username, const std::string& password,
        UserProfile profile);

    Trainee(int id, const std::string& username, const std::string& password,
        UserProfile profile);

    void addFoodEntry(const FoodEntry& entry);
    void addExerciseEntry(const ExerciseEntry& entry);
    void addGoal(const FitnessGoal& goal);
    void addFavoriteExercise(const Exercise& ex);

    void logFood(Calorix& system);
    void logExercise(Calorix& system);
    void viewDailySummary() const;
    void viewProgress() const;

    const std::vector<FoodEntry>& getFoodDiary()         const;
    const std::vector<ExerciseEntry>& getExerciseDiary()     const;
    const std::vector<FitnessGoal>& getGoals()             const;
    const std::vector<Exercise>& getFavoriteExercises() const;

    void help() const override;
    ~Trainee() override = default;
};

