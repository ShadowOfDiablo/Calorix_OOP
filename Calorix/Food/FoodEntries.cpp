#include "FoodEntries.h"
#include<stdexcept>

int FoodEntry::idGenerator = 0;

FoodEntry::FoodEntry(Food& food,
    double quantityGrams,
    const Date& date)
    : entryId(++idGenerator),
    food(food),
    quantityGrams(quantityGrams),
    date(date)
{
    if (quantityGrams <= 0) {
        throw std::invalid_argument("Don't lie to me! It is not possible to eat negative food. You wish! Be honest and give me a positive number:");
    }
}

int FoodEntry::getEntryId() const {
    return entryId;
}

const Food& FoodEntry::getFood() const {
    return food;
}

double FoodEntry::getQuantityGrams() const {
    return quantityGrams;
}

Date FoodEntry::getDate() const {
    return date;
}


double FoodEntry::calculateCalories() const {
    return (food.getCaloriesPer100g() * quantityGrams) / 100.0;
}

double FoodEntry::calculateProtein() const {
    return (food.getProteinPer100g() * quantityGrams) / 100.0;
}

double FoodEntry::calculateCarbs() const {
    return (food.getCarbsPer100g() * quantityGrams) / 100.0;
}

double FoodEntry::calculateFat() const {
    return (food.getFatPer100g() * quantityGrams) / 100.0;
}