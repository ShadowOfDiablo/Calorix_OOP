#pragma once

#include "Exercise.h"
#include "../Date.h"

class ExerciseEntry {
private:
   int entryId;
   const Exercise& exercise;
   int durationMinutes;
   Date date;

public:
    static int idGenerator;
    ExerciseEntry(const Exercise& exercise,
        int durationMinutes,
        const Date& date);
   

    int getEntryId() const;

    const Exercise& getExercise() const;

    int getDurationMinutes() const;

    Date getDate() const;

    double calculateBurnedCalories() const;
};