#ifndef EXERCISE_H
#define EXERCISE_H

#include <string>

enum class MuscleGroup
{
    CHEST,
    BACK,
    LEGS,
    SHOULDERS,
    ARMS,
    CORE,
    CARDIO
};

class Exercise
{
private:
    int         s8ExerciseId;
    std::string name;
    double      f32CaloriesBurnedPerHour;
    MuscleGroup muscleGroup;

public:
    static int s8IdGenerator;

    Exercise(const std::string& name,
             double f32CaloriesBurnedPerHour,
             MuscleGroup muscleGroup);

    Exercise(int s8Id,
             const std::string& name,
             double f32CaloriesBurnedPerHour,
             MuscleGroup muscleGroup);

    int         getExerciseId()            const;
    std::string getName()                  const;
    double      getCaloriesBurnedPerHour() const;
    MuscleGroup getMuscleGroup()           const;

    static void setIdGenerator(int s8Val);
};

#endif // EXERCISE_H
