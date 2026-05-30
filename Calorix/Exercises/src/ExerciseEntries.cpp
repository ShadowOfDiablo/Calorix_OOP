#include "ExerciseEntries.h"
#include <stdexcept>

int ExerciseEntry::s8IdGenerator = 0;

ExerciseEntry::ExerciseEntry(const Exercise& exercise, int s8DurationMinutes, const Date& date)
    : s8EntryId(++s8IdGenerator),
      exercise(exercise),
      s8DurationMinutes(s8DurationMinutes),
      date(date)
{
    if(s8DurationMinutes < 0)
    {
        throw std::invalid_argument("I know you were lazy today, but your duration must be at least positive number!");
    }
}

int             ExerciseEntry::getEntryId()         const { return s8EntryId; }
const Exercise& ExerciseEntry::getExercise()        const { return exercise; }
int             ExerciseEntry::getDurationMinutes()  const { return s8DurationMinutes; }
Date            ExerciseEntry::getDate()             const { return date; }

double ExerciseEntry::calculateBurnedCalories() const
{
    return (exercise.getCaloriesBurnedPerHour() * s8DurationMinutes) / 60.0;
}
