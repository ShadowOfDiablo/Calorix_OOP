#include <iostream>
#include <unordered_map>
#include "Calorix.h"
#include "Admin.h"
#include "Trainee.h"

static GoalType parseGoalType(const std::string& s)
{
    if(s == "WEIGHT_LOSS") return GoalType::WEIGHT_LOSS;
    if(s == "BULKING")     return GoalType::BULKING;
    return GoalType::MAINTENANCE;
}

static void runTraineeSession(Trainee* trainee, Calorix& system)
{
    trainee->help();
    std::string cmd;
    while(std::cin >> cmd && cmd != "logout")
    {
        if(cmd == "log-food")
            trainee->logFood(system);
        else if(cmd == "log-exercise")
            trainee->logExercise(system);
        else if(cmd == "view-daily-summary")
            trainee->viewDailySummary();
        else if(cmd == "view-progress")
            trainee->viewProgress();
        else if(cmd == "calculate-bmi")
            trainee->calculateBMI();
        else if(cmd == "calculate-bmr")
            trainee->calculateBMR();
        else if(cmd == "add-to-favorites")
            trainee->addToFavorites(system);
        else if(cmd == "view-favorites")
            trainee->viewFavorites();
        else if(cmd == "set-goals")
        {
            std::string typeStr;
            double target;
            int sd, sm, sy, dd, dm, dy;
            std::cout << "Enter goal type (WEIGHT_LOSS/BULKING/MAINTENANCE), target value, "
                         "start date (dd mm yyyy), deadline (dd mm yyyy):\n";
            std::cin >> typeStr >> target >> sd >> sm >> sy >> dd >> dm >> dy;
            trainee->addGoal(FitnessGoal(parseGoalType(typeStr), target,
                Date(sd, sm, sy), Date(dd, dm, dy)));
            std::cout << "Goal added.\n";
        }
        else if(cmd == "generate-workout-plan")
            std::cout << "Not yet implemented.\n";
        else
            std::cout << "Unknown command. Type 'logout' to exit.\n";
    }
    std::cout << "Logged out.\n";
}

static void runAdminSession(Admin* admin, Calorix& system)
{
    admin->help();
    std::string cmd;
    while(std::cin >> cmd && cmd != "logout")
    {
        if(cmd == "add-food")
            admin->addFood(system);
        else if(cmd == "add-exercise")
            admin->addExercise(system);
        else if(cmd == "update-food")
            admin->updateFood(system);
        else if(cmd == "block-user")
        {
            std::string username;
            std::cin >> username;
            admin->blockUser(username, system);
        }
        else
            std::cout << "Unknown command. Type 'logout' to exit.\n";
    }
    std::cout << "Logged out.\n";
}

static Gender parseGender(const std::string& s)
{
    if(s == "MALE")   return Gender::MALE;
    if(s == "FEMALE") return Gender::FEMALE;
    return Gender::OTHER;
}

static ActivityLevel parseActivityLevel(const std::string& s)
{
    static const std::unordered_map<std::string, ActivityLevel> table = {
        {"SEDENTARY",  ActivityLevel::SEDENTARY},
        {"LIGHT",      ActivityLevel::LIGHT},
        {"MODERATE",   ActivityLevel::MODERATE},
        {"ACTIVE",     ActivityLevel::ACTIVE},
        {"VERY_ACTIVE", ActivityLevel::VERY_ACTIVE},
    };
    auto it = table.find(s);
    if(it != table.end())
        return it->second;
    return ActivityLevel::SEDENTARY;
}

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
            User* logged = system.login(user, password);
            if(!logged)
            {
                std::cout << "Wrong credentials\n";
            }
            else
            {
                std::cout << "Welcome back " << user << "!\n";
                if(Admin* admin = dynamic_cast<Admin*>(logged))
                    runAdminSession(admin, system);
                else if(Trainee* trainee = dynamic_cast<Trainee*>(logged))
                    runTraineeSession(trainee, system);
            }
        }
        else if(input == "2")
        {
            std::string type;
            std::cout << "Register as (trainee/admin):\n";
            std::cin >> type;

            std::string username, password;
            std::cout << "Enter username and password:\n";
            std::cin >> username >> password;

            if(type == "admin")
            {
                std::string key;
                std::cout << "Enter admin key:\n";
                std::cin >> key;
                if(!system.registerAdmin(username, password, key))
                    std::cout << "Username '" << username << "' already taken.\n";
                else
                    std::cout << "Admin registered.\n";
            }
            else
            {
                int age;
                double weight, height;
                std::string genderStr, activityStr;
                std::cout << "Enter age, weight (kg), height (m):\n";
                std::cin >> age >> weight >> height;
                std::cout << "Enter gender (MALE/FEMALE/OTHER):\n";
                std::cin >> genderStr;
                std::cout << "Enter activity level (SEDENTARY/LIGHT/MODERATE/ACTIVE/VERY_ACTIVE):\n";
                std::cin >> activityStr;

                if(!system.registerTrainee(username, password, age, weight, height,
                    parseGender(genderStr), parseActivityLevel(activityStr)))
                    std::cout << "Username '" << username << "' already taken.\n";
                else
                    std::cout << "Trainee registered.\n";
            }
        }
        else if(input == "4")
        {
            runTest(system);
        }
    }

    return 0;
}
