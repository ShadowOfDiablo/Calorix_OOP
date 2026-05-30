#include "Exercise.h"

int Exercise::s8IdGenerator = 0;

Exercise::Exercise(const std::string& name,
                   double f32CaloriesBurnedPerHour,
                   MuscleGroup muscleGroup)
    : s8ExerciseId(++s8IdGenerator),
      name(name),
      f32CaloriesBurnedPerHour(f32CaloriesBurnedPerHour),
      muscleGroup(muscleGroup)
{
}

Exercise::Exercise(int s8Id,
                   const std::string& name,
                   double f32CaloriesBurnedPerHour,
                   MuscleGroup muscleGroup)
    : s8ExerciseId(s8Id),
      name(name),
      f32CaloriesBurnedPerHour(f32CaloriesBurnedPerHour),
      muscleGroup(muscleGroup)
{
}

int         Exercise::getExerciseId()            const { return s8ExerciseId; }
std::string Exercise::getName()                  const { return name; }
double      Exercise::getCaloriesBurnedPerHour() const { return f32CaloriesBurnedPerHour; }
MuscleGroup Exercise::getMuscleGroup()           const { return muscleGroup; }

void Exercise::setIdGenerator(int s8Val) { s8IdGenerator = s8Val; }
