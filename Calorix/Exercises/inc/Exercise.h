#pragma once
#include <string>

enum class MuscleGroup {
    CHEST,
    BACK,
    LEGS,
    SHOULDERS,
    ARMS,
    CORE,
    CARDIO
};

class Exercise {
private:
    int exerciseId;
    std::string name;
    double caloriesBurnedPerHour;
    MuscleGroup muscleGroup;

public:
    static int idGenerator;
    Exercise(const std::string& name,
        double caloriesBurnedPerHour,
        MuscleGroup muscleGroup);

    Exercise(int id,
        const std::string& name,
        double caloriesBurnedPerHour,
        MuscleGroup muscleGroup);

    int getExerciseId() const;

    std::string getName() const;

    double getCaloriesBurnedPerHour() const;

    MuscleGroup getMuscleGroup() const;

    static void setIdGenerator(int val);
};
