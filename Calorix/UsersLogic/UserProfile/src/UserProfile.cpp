#include "UserProfile.h"

UserProfile::UserProfile(int s8Age,
                         double f32Weight,
                         double f32Height,
                         Gender gender,
                         ActivityLevel activityLevel)
    : s8Age(s8Age),
      f32Weight(f32Weight),
      f32Height(f32Height),
      gender(gender),
      activityLevel(activityLevel)
{
}

int           UserProfile::getAge()           const { return s8Age; }
double        UserProfile::getWeight()        const { return f32Weight; }
double        UserProfile::getHeight()        const { return f32Height; }
Gender        UserProfile::getGender()        const { return gender; }
ActivityLevel UserProfile::getActivityLevel() const { return activityLevel; }
