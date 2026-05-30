#ifndef FITNESS_GOAL_H
#define FITNESS_GOAL_H

#include "Date.h"

enum class GoalType
{
    WEIGHT_LOSS,
    BULKING,
    MAINTENANCE
};

class FitnessGoal
{
private:
    GoalType goalType;
    double   f32TargetValue;
    Date     startDate;
    Date     deadline;
    bool     isAchieved;

public:
    FitnessGoal(GoalType goalType,
                double f32TargetValue,
                const Date& startDate,
                const Date& deadline);

    GoalType getGoalType()    const;
    double   getTargetValue() const;
    Date     getStartDate()   const;
    Date     getDeadline()    const;
    bool     getIsAchieved()  const;

    void completeGoal();
};

#endif // FITNESS_GOAL_H
