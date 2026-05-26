#pragma once
#include <string>
enum class ActivityLevel {
    SEDENTARY,
    LIGHT,
    MODERATE,
    ACTIVE,
    VERY_ACTIVE
};

enum class Gender {
    FEMALE,
    MALE,
    OTHER
};

class UserProfile {
private:
    int age;
    double weight;
    double height;
    Gender gender;
    ActivityLevel activityLevel;

public:
    UserProfile(
        int age,
        double weight,
        double height,
        Gender gender,
        ActivityLevel activityLevel
    );
    UserProfile() = default;

    int getAge() const;
    double getWeight() const;
    double getHeight() const;
    Gender getGender() const;
    ActivityLevel getActivityLevel() const;
};