#include "FitnessGoal.h"

FitnessGoal::FitnessGoal(GoalType goalType,
                         double f32TargetValue,
                         const Date& startDate,
                         const Date& deadline)
    : goalType(goalType),
      f32TargetValue(f32TargetValue),
      startDate(startDate),
      deadline(deadline),
      isAchieved(false)
{
}

GoalType FitnessGoal::getGoalType()    const { return goalType; }
double   FitnessGoal::getTargetValue() const { return f32TargetValue; }
Date     FitnessGoal::getStartDate()   const { return startDate; }
Date     FitnessGoal::getDeadline()    const { return deadline; }
bool     FitnessGoal::getIsAchieved()  const { return isAchieved; }

void FitnessGoal::completeGoal()
{
    isAchieved = true;
}
