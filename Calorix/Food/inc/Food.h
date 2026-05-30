#ifndef FOOD_H
#define FOOD_H

#include <string>

class Food
{
private:
    int         s8FoodId;
    std::string name;
    int         s8CaloriesPer100g;
    int         s8ProteinPer100g;
    int         s8CarbsPer100g;
    int         s8FatPer100g;

public:
    static int s8IdGenerator;

    Food(const std::string& name,
         int s8CaloriesPer100g,
         int s8ProteinPer100g,
         int s8CarbsPer100g,
         int s8FatPer100g);

    Food(int s8Id,
         const std::string& name,
         int s8CaloriesPer100g,
         int s8ProteinPer100g,
         int s8CarbsPer100g,
         int s8FatPer100g);

    int         getId()              const;
    std::string getName()            const;
    int         getCaloriesPer100g() const;
    int         getProteinPer100g()  const;
    int         getCarbsPer100g()    const;
    int         getFatPer100g()      const;

    void setCaloriesPer100g(int s8Cal);
    static void setIdGenerator(int s8Val);
};

#endif // FOOD_H
