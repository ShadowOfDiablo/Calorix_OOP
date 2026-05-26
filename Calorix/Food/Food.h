#pragma once
#include <string>

class Food {
private:
    int foodId;
    std::string name;
    int caloriesPer100g;
    int proteinPer100g;
    int carbsPer100g;
    int fatPer100g;

public:
    static int idGenerator;


    Food(const std::string& name,
        int caloriesPer100g,
        int proteinPer100g,
        int carbsPer100g,
        int fatPer100g);


    Food(int id,
        const std::string& name,
        int caloriesPer100g,
        int proteinPer100g,
        int carbsPer100g,
        int fatPer100g);

    int getId() const;
    std::string getName() const;
    int getCaloriesPer100g() const;
    int getProteinPer100g() const;
    int getCarbsPer100g() const;
    int getFatPer100g() const;


    void setCaloriesPer100g(int cal);


    static void setIdGenerator(int val);
};