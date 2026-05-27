#include "UserProfile.h"

UserProfile::UserProfile(
    int age,
    double weight,
    double height,
    Gender gender,
    ActivityLevel activityLevel):age(age),weight(weight),height(height),gender(gender),activityLevel(activityLevel)
{}

int UserProfile::getAge() const {
    return age;
}

double UserProfile::getWeight() const {
    return weight;
}

double UserProfile::getHeight() const {
    return height;
}

Gender UserProfile::getGender() const {
    return gender;
}

ActivityLevel UserProfile::getActivityLevel() const {
    return activityLevel;
}