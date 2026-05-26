#pragma once

#include "../Date.h"

enum class GoalType {
    WEIGHT_LOSS,
    BULKING,
    MAINTENANCE
};

class FitnessGoal {
private:
    GoalType goalType;
    double targetValue;
    Date startDate;
    Date deadline;
    bool isAchieved;

public:
    FitnessGoal(GoalType goalType,
        double targetValue,
        const Date& startDate,
        const Date& deadline);

    GoalType getGoalType() const;

    double getTargetValue() const;

    Date getStartDate() const;

    Date getDeadline() const;

    bool getIsAchieved() const;

    void completeGoal();
};
