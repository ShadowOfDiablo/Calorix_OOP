#ifndef USER_PROFILE_H
#define USER_PROFILE_H

#include <string>

enum class ActivityLevel
{
    SEDENTARY,
    LIGHT,
    MODERATE,
    ACTIVE,
    VERY_ACTIVE
};

enum class Gender
{
    FEMALE,
    MALE,
    OTHER
};

class UserProfile
{
private:
    int           s8Age;
    double        f32Weight;
    double        f32Height;
    Gender        gender;
    ActivityLevel activityLevel;

public:
    UserProfile(int s8Age,
                double f32Weight,
                double f32Height,
                Gender gender,
                ActivityLevel activityLevel);
    UserProfile() = default;

    int           getAge()           const;
    double        getWeight()        const;
    double        getHeight()        const;
    Gender        getGender()        const;
    ActivityLevel getActivityLevel() const;
};

#endif // USER_PROFILE_H
