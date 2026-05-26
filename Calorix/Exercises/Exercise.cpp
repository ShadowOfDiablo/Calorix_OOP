#include "Exercise.h"

int Exercise::idGenerator = 0;

Exercise::Exercise(const std::string& name,
    double caloriesBurnedPerHour,
    MuscleGroup muscleGroup)
    : exerciseId(++idGenerator),
    name(name),
    caloriesBurnedPerHour(caloriesBurnedPerHour),
    muscleGroup(muscleGroup)
{
}
Exercise::Exercise(int id,
    const std::string& name,
    double caloriesBurnedPerHour,
    MuscleGroup muscleGroup)
    : exerciseId(id),
    name(name),
    caloriesBurnedPerHour(caloriesBurnedPerHour),
    muscleGroup(muscleGroup)
{
}


int Exercise::getExerciseId() const {
    return exerciseId;
}

std::string Exercise::getName() const {
    return name;
}

double Exercise::getCaloriesBurnedPerHour() const {
    return caloriesBurnedPerHour;
}

MuscleGroup Exercise::getMuscleGroup() const {
    return muscleGroup;
}

void Exercise::setIdGenerator(int val) { idGenerator = val; }