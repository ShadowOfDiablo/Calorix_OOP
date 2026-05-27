#include "ExerciseEntries.h"
#include<stdexcept>

int ExerciseEntry::idGenerator = 0;

ExerciseEntry::ExerciseEntry(const Exercise& exercise,
    int durationMinutes,
    const Date& date)
    : entryId(++idGenerator),
    exercise(exercise),
    durationMinutes(durationMinutes),
    date(date)
{
    if (durationMinutes<0) 
    {
        throw std::invalid_argument("I know you were lazy today, but your duration must be at least positive number!");
    }
}


int ExerciseEntry::getEntryId() const {
    return entryId;
}

const Exercise& ExerciseEntry::getExercise() const {
    return exercise;
}

int ExerciseEntry::getDurationMinutes() const {
    return durationMinutes;
}

Date ExerciseEntry::getDate() const {
    return date;
}


double ExerciseEntry::calculateBurnedCalories() const {
    return (exercise.getCaloriesBurnedPerHour() * durationMinutes) / 60.0;
}
