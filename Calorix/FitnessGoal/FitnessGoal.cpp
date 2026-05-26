#include "FitnessGoal.h"

FitnessGoal::FitnessGoal(GoalType goalType,
    double targetValue,
    const Date& startDate,
    const Date& deadline)
    : goalType(goalType),
    targetValue(targetValue),
    startDate(startDate),
    deadline(deadline),
    isAchieved(false)
{
}

GoalType FitnessGoal::getGoalType() const {
    return goalType;
}

double FitnessGoal::getTargetValue() const {
    return targetValue;
}

Date FitnessGoal::getStartDate() const {
    return startDate;
}

Date FitnessGoal::getDeadline() const {
    return deadline;
}

bool FitnessGoal::getIsAchieved() const {
    return isAchieved;
}


void FitnessGoal::completeGoal() {
    isAchieved = true;
}
