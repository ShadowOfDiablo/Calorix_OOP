#include "FoodEntries.h"
#include <stdexcept>

int FoodEntry::s8IdGenerator = 0;

FoodEntry::FoodEntry(Food& food, double f32QuantityGrams, const Date& date)
    : s8EntryId(++s8IdGenerator),
      food(food),
      f32QuantityGrams(f32QuantityGrams),
      date(date)
{
    if(f32QuantityGrams <= 0)
    {
        throw std::invalid_argument("Don't lie to me! It is not possible to eat negative food. You wish! Be honest and give me a positive number:");
    }
}

int         FoodEntry::getEntryId()       const { return s8EntryId; }
const Food& FoodEntry::getFood()          const { return food; }
double      FoodEntry::getQuantityGrams() const { return f32QuantityGrams; }
Date        FoodEntry::getDate()          const { return date; }

double FoodEntry::calculateCalories() const { return (food.getCaloriesPer100g() * f32QuantityGrams) / 100.0; }
double FoodEntry::calculateProtein()  const { return (food.getProteinPer100g()  * f32QuantityGrams) / 100.0; }
double FoodEntry::calculateCarbs()    const { return (food.getCarbsPer100g()    * f32QuantityGrams) / 100.0; }
double FoodEntry::calculateFat()      const { return (food.getFatPer100g()      * f32QuantityGrams) / 100.0; }
