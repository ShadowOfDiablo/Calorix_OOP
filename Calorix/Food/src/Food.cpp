#include "Food.h"

int Food::s8IdGenerator = 0;

Food::Food(const std::string& name,
           int s8CaloriesPer100g,
           int s8ProteinPer100g,
           int s8CarbsPer100g,
           int s8FatPer100g)
    : s8FoodId(++s8IdGenerator),
      name(name),
      s8CaloriesPer100g(s8CaloriesPer100g),
      s8ProteinPer100g(s8ProteinPer100g),
      s8CarbsPer100g(s8CarbsPer100g),
      s8FatPer100g(s8FatPer100g)
{
}

Food::Food(int s8Id,
           const std::string& name,
           int s8CaloriesPer100g,
           int s8ProteinPer100g,
           int s8CarbsPer100g,
           int s8FatPer100g)
    : s8FoodId(s8Id),
      name(name),
      s8CaloriesPer100g(s8CaloriesPer100g),
      s8ProteinPer100g(s8ProteinPer100g),
      s8CarbsPer100g(s8CarbsPer100g),
      s8FatPer100g(s8FatPer100g)
{
}

int         Food::getId()              const { return s8FoodId; }
std::string Food::getName()            const { return name; }
int         Food::getCaloriesPer100g() const { return s8CaloriesPer100g; }
int         Food::getProteinPer100g()  const { return s8ProteinPer100g; }
int         Food::getCarbsPer100g()    const { return s8CarbsPer100g; }
int         Food::getFatPer100g()      const { return s8FatPer100g; }

void Food::setCaloriesPer100g(int s8Cal) { s8CaloriesPer100g = s8Cal; }
void Food::setIdGenerator(int s8Val)     { s8IdGenerator = s8Val; }
