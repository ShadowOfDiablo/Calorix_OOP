#include <iostream>
#include "Calorix.h"
#include "Admin.h"
#include "Trainee.h"

static void runTest(Calorix& system)
{
    std::cout << "=== Running test ===\n\n";

    // --- Admin setup ---
    bool adminOk = system.registerAdmin("admin1", "adminpass", "SECRET");
    std::cout << "Register admin1: " << (adminOk ? "OK" : "FAIL") << "\n";

    User* adminUser = system.login("admin1", "adminpass");
    std::cout << "Login admin1: " << (adminUser ? "OK" : "FAIL") << "\n";

    Admin* admin = dynamic_cast<Admin*>(adminUser);

    system.addFood("Chicken", 165, 31, 0, 4);
    system.addFood("Rice", 130, 3, 28, 1);
    system.addExercise("Running", 600.0, MuscleGroup::CARDIO);
    system.addExercise("Squats", 400.0, MuscleGroup::LEGS);
    std::cout << "Admin added 2 foods and 2 exercises.\n";

    // Duplicate food should fail
    bool dupFood = system.addFood("Chicken", 165, 31, 0, 4);
    std::cout << "Add duplicate Chicken: " << (!dupFood ? "correctly rejected" : "FAIL") << "\n";

    // Update food
    bool updated = system.updateFood("Rice", 140);
    std::cout << "Update Rice calories: " << (updated ? "OK" : "FAIL") << "\n";

    // --- Trainee setup ---
    bool traineeOk = system.registerTrainee(
        "trainee1", "pass123",
        25, 80.0, 1.80,
        Gender::MALE, ActivityLevel::MODERATE
    );
    std::cout << "Register trainee1: " << (traineeOk ? "OK" : "FAIL") << "\n";

    // Duplicate username should fail
    bool dupUser = system.registerTrainee(
        "trainee1", "other",
        20, 70.0, 1.75,
        Gender::FEMALE, ActivityLevel::LIGHT
    );
    std::cout << "Register duplicate trainee1: " << (!dupUser ? "correctly rejected" : "FAIL") << "\n";

    User* traineeUser = system.login("trainee1", "pass123");
    std::cout << "Login trainee1: " << (traineeUser ? "OK" : "FAIL") << "\n";

    Trainee* trainee = dynamic_cast<Trainee*>(traineeUser);

    // Wrong password
    User* badLogin = system.login("trainee1", "wrongpass");
    std::cout << "Login with wrong password: " << (!badLogin ? "correctly rejected" : "FAIL") << "\n";

    // --- Trainee actions ---
    Food* chicken = system.findFood("Chicken");
    Food* rice    = system.findFood("Rice");
    Exercise* running = system.findExercise("Running");
    Exercise* squats  = system.findExercise("Squats");

    trainee->addFoodEntry(FoodEntry(*chicken, 200.0, Date::today()));
    trainee->addFoodEntry(FoodEntry(*rice,    150.0, Date::today()));
    trainee->addExerciseEntry(ExerciseEntry(*running, 30, Date::today()));
    trainee->addExerciseEntry(ExerciseEntry(*squats,  20, Date::today()));
    std::cout << "\nLogged food and exercise entries.\n";

    trainee->addFavoriteExercise(*running);
    trainee->addFavoriteExercise(*squats);

    std::cout << "\n";
    trainee->viewDailySummary();

    std::cout << "\n";
    trainee->viewProgress();

    std::cout << "\n";
    trainee->viewFavorites();

    std::cout << "\n";
    trainee->calculateBMI();
    trainee->calculateBMR();

    // --- Block user ---
    std::cout << "\n";
    bool blocked = system.blockUser("trainee1");
    std::cout << "Block trainee1: " << (blocked ? "OK" : "FAIL") << "\n";

    User* afterBlock = system.login("trainee1", "pass123");
    std::cout << "Login after block: " << (!afterBlock ? "correctly rejected" : "FAIL") << "\n";

    std::cout << "\n=== Test complete ===\n\n";
}

int main()
{
    Calorix system;
    std::cout << "Please select an option\n";
    std::cout << "1: login\n";
    std::cout << "2: register\n";
    std::cout << "3: load from file\n";
    std::cout << "4: run test\n";

    std::string input;
    while(std::cin >> input && input != "end")
    {
        if(input == "1")
        {
            std::string user, password;
            std::cout << "Enter your username and password:\n";
            std::cin >> user >> password;
            if(system.login(user, password) != nullptr)
            {
                std::cout << "Welcome back " << user << "!\n";
            }
            else
            {
                std::cout << "Wrong credentials\n";
            }
        }
        else if(input == "2")
        {
            std::string user, password;
            std::cout << "Enter your username and password:\n";
            std::cin >> user >> password;
            // system.registerTrainee()
        }
        else if(input == "4")
        {
            runTest(system);
        }
    }

    return 0;
}
