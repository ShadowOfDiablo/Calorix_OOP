#pragma once

#include "Food.h"
#include "../Date.h"

class FoodEntry {
private:
    int entryId;
    Food& food;
    double quantityGrams;
    Date date;

public:
    static int idGenerator;
    FoodEntry(Food& food,
        double quantityGrams,
        const Date& date);

    int getEntryId() const;

    const Food& getFood() const;

    double getQuantityGrams() const;

    Date getDate() const;

    double calculateCalories() const;

    double calculateProtein() const;

    double calculateCarbs() const;

    double calculateFat() const;
};

