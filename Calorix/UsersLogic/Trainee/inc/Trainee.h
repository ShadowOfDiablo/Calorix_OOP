#pragma once
#include "User.h"
#include "../Food/FoodEntries.h"
#include "../Exercises/ExerciseEntries.h"
#include "../FitnessGoal/FitnessGoal.h"
#include "../Exercises/Exercise.h"
#include <vector>

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

    const std::vector<FoodEntry>& getFoodDiary()         const;
    const std::vector<ExerciseEntry>& getExerciseDiary()     const;
    const std::vector<FitnessGoal>& getGoals()             const;
    const std::vector<Exercise>& getFavoriteExercises() const;

    void help() const override;
    ~Trainee() override = default;
};

