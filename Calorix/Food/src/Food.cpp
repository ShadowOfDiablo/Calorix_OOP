#include "Food.h"

int Food::idGenerator = 0;

Food::Food(const std::string& name,
    int caloriesPer100g,
    int proteinPer100g,
    int carbsPer100g,
    int fatPer100g)
    : foodId(++idGenerator),
    name(name),
    caloriesPer100g(caloriesPer100g),
    proteinPer100g(proteinPer100g),
    carbsPer100g(carbsPer100g),
    fatPer100g(fatPer100g)
{
}


Food::Food(int id,
    const std::string& name,
    int caloriesPer100g,
    int proteinPer100g,
    int carbsPer100g,
    int fatPer100g)
    : foodId(id),
    name(name),
    caloriesPer100g(caloriesPer100g),
    proteinPer100g(proteinPer100g),
    carbsPer100g(carbsPer100g),
    fatPer100g(fatPer100g)
{
}

int Food::getId()              const { return foodId; }
std::string Food::getName()    const { return name; }
int Food::getCaloriesPer100g() const { return caloriesPer100g; }
int Food::getProteinPer100g()  const { return proteinPer100g; }
int Food::getCarbsPer100g()    const { return carbsPer100g; }
int Food::getFatPer100g()      const { return fatPer100g; }

void Food::setCaloriesPer100g(int cal) { caloriesPer100g = cal; }
void Food::setIdGenerator(int val) { idGenerator = val; }