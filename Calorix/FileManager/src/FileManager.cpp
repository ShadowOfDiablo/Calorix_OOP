#include "FileManager.h"
#include "Calorix.h"
#include "Admin.h"
#include "Trainee.h"
#include "Food.h"
#include "FoodEntries.h"
#include "Exercise.h"
#include "ExerciseEntries.h"
#include "FitnessGoal.h"
#include "Date.h"
#include "UserProfile.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

// ── helpers ───────────────────────────────────────────────────────────────────

static std::vector<std::string> splitLine(const std::string& line, char delim)
{
    std::vector<std::string> tokens;
    std::stringstream ss(line);
    std::string token;
    while(std::getline(ss, token, delim))
        tokens.push_back(token);
    return tokens;
}

static std::string muscleGroupToStr(MuscleGroup mg)
{
    switch(mg)
    {
        case MuscleGroup::CHEST:      return "CHEST";
        case MuscleGroup::BACK:       return "BACK";
        case MuscleGroup::LEGS:       return "LEGS";
        case MuscleGroup::SHOULDERS:  return "SHOULDERS";
        case MuscleGroup::ARMS:       return "ARMS";
        case MuscleGroup::CORE:       return "CORE";
        case MuscleGroup::CARDIO:     return "CARDIO";
    }
    return "CARDIO";
}

static MuscleGroup strToMuscleGroup(const std::string& s)
{
    if(s == "CHEST")     return MuscleGroup::CHEST;
    if(s == "BACK")      return MuscleGroup::BACK;
    if(s == "LEGS")      return MuscleGroup::LEGS;
    if(s == "SHOULDERS") return MuscleGroup::SHOULDERS;
    if(s == "ARMS")      return MuscleGroup::ARMS;
    if(s == "CORE")      return MuscleGroup::CORE;
    return MuscleGroup::CARDIO;
}

static std::string goalTypeToStr(GoalType gt)
{
    switch(gt)
    {
        case GoalType::WEIGHT_LOSS:  return "WEIGHT_LOSS";
        case GoalType::BULKING:      return "BULKING";
        case GoalType::MAINTENANCE:  return "MAINTENANCE";
    }
    return "MAINTENANCE";
}

static GoalType strToGoalType(const std::string& s)
{
    if(s == "WEIGHT_LOSS") return GoalType::WEIGHT_LOSS;
    if(s == "BULKING")     return GoalType::BULKING;
    return GoalType::MAINTENANCE;
}

static std::string genderToStr(Gender g)
{
    switch(g)
    {
        case Gender::MALE:   return "MALE";
        case Gender::FEMALE: return "FEMALE";
        case Gender::OTHER:  return "OTHER";
    }
    return "OTHER";
}

static Gender strToGender(const std::string& s)
{
    if(s == "MALE")   return Gender::MALE;
    if(s == "FEMALE") return Gender::FEMALE;
    return Gender::OTHER;
}

static std::string activityLevelToStr(ActivityLevel al)
{
    switch(al)
    {
        case ActivityLevel::SEDENTARY:   return "SEDENTARY";
        case ActivityLevel::LIGHT:       return "LIGHT";
        case ActivityLevel::MODERATE:    return "MODERATE";
        case ActivityLevel::ACTIVE:      return "ACTIVE";
        case ActivityLevel::VERY_ACTIVE: return "VERY_ACTIVE";
    }
    return "SEDENTARY";
}

static ActivityLevel strToActivityLevel(const std::string& s)
{
    if(s == "LIGHT")       return ActivityLevel::LIGHT;
    if(s == "MODERATE")    return ActivityLevel::MODERATE;
    if(s == "ACTIVE")      return ActivityLevel::ACTIVE;
    if(s == "VERY_ACTIVE") return ActivityLevel::VERY_ACTIVE;
    return ActivityLevel::SEDENTARY;
}

// ── save ──────────────────────────────────────────────────────────────────────

void FileManager::save(const Calorix& system, const std::string& filename)
{
    std::ofstream out(filename);
    if(!out)
    {
        std::cerr << "Cannot open file for writing: " << filename << "\n";
        return;
    }

    out << "# Calorix save file v1\n\n";

    out << "[METADATA]\n";
    out << "food_id_gen|"           << Food::s8IdGenerator          << "\n";
    out << "exercise_id_gen|"       << Exercise::s8IdGenerator      << "\n";
    out << "food_entry_id_gen|"     << FoodEntry::s8IdGenerator     << "\n";
    out << "exercise_entry_id_gen|" << ExerciseEntry::s8IdGenerator << "\n";
    out << "user_id_gen|"           << User::s8IdGenerator          << "\n\n";

    out << "[FOOD]\n";
    for(const auto& pair : system.foods)
    {
        const Food& f = pair.second;
        out << f.getId()              << "|"
            << f.getName()            << "|"
            << f.getCaloriesPer100g() << "|"
            << f.getProteinPer100g()  << "|"
            << f.getCarbsPer100g()    << "|"
            << f.getFatPer100g()      << "\n";
    }
    out << "\n";

    out << "[EXERCISE]\n";
    for(const auto& pair : system.exercises)
    {
        const Exercise& e = pair.second;
        out << e.getExerciseId()                     << "|"
            << e.getName()                           << "|"
            << e.getCaloriesBurnedPerHour()          << "|"
            << muscleGroupToStr(e.getMuscleGroup())  << "\n";
    }
    out << "\n";

    for(const auto& pair : system.users)
    {
        const User* p_user = pair.second.get();

        if(const Admin* p_admin = dynamic_cast<const Admin*>(p_user))
        {
            out << "[USER:ADMIN]\n";
            out << p_admin->getId()       << "|"
                << p_admin->getUsername() << "|"
                << p_admin->getPassword() << "|"
                << p_admin->getAdminKey() << "\n\n";
        }
        else if(const Trainee* p_trainee = dynamic_cast<const Trainee*>(p_user))
        {
            const std::string& uname = p_trainee->getUsername();
            const UserProfile& prof  = p_trainee->getProfile();

            out << "[USER:TRAINEE]\n";
            out << p_trainee->getId()                        << "|"
                << uname                                     << "|"
                << p_trainee->getPassword()                  << "|"
                << prof.getAge()                             << "|"
                << prof.getWeight()                          << "|"
                << prof.getHeight()                          << "|"
                << genderToStr(prof.getGender())             << "|"
                << activityLevelToStr(prof.getActivityLevel()) << "\n";

            out << "[FOOD_DIARY:" << uname << "]\n";
            for(const auto& entry : p_trainee->getFoodDiary())
            {
                const Date& d = entry.getDate();
                out << entry.getEntryId()        << "|"
                    << entry.getFood().getName() << "|"
                    << entry.getQuantityGrams()  << "|"
                    << d.getDay()   << "|"
                    << d.getMonth() << "|"
                    << d.getYear()  << "\n";
            }

            out << "[EXERCISE_DIARY:" << uname << "]\n";
            for(const auto& entry : p_trainee->getExerciseDiary())
            {
                const Date& d = entry.getDate();
                out << entry.getEntryId()            << "|"
                    << entry.getExercise().getName() << "|"
                    << entry.getDurationMinutes()    << "|"
                    << d.getDay()   << "|"
                    << d.getMonth() << "|"
                    << d.getYear()  << "\n";
            }

            out << "[GOALS:" << uname << "]\n";
            for(const auto& goal : p_trainee->getGoals())
            {
                const Date& s  = goal.getStartDate();
                const Date& dl = goal.getDeadline();
                out << goalTypeToStr(goal.getGoalType()) << "|"
                    << goal.getTargetValue()             << "|"
                    << s.getDay()   << "|" << s.getMonth()  << "|" << s.getYear()  << "|"
                    << dl.getDay()  << "|" << dl.getMonth() << "|" << dl.getYear() << "|"
                    << (goal.getIsAchieved() ? 1 : 0)    << "\n";
            }

            out << "[FAVORITES:" << uname << "]\n";
            for(const auto& ex : p_trainee->getFavoriteExercises())
                out << ex.getName() << "\n";

            out << "\n";
        }
    }

    std::cout << "Saved to " << filename << "\n";
}

// ── load ──────────────────────────────────────────────────────────────────────

void FileManager::load(Calorix& system, const std::string& filename)
{
    std::ifstream in(filename);
    if(!in)
    {
        std::cerr << "Cannot open file for reading: " << filename << "\n";
        return;
    }

    // Metadata values — applied after all objects are loaded so that id generators
    // are not disturbed by constructors called during loading.
    int metaFoodId = -1, metaExerciseId = -1, metaFoodEntryId = -1;
    int metaExerciseEntryId = -1, metaUserId = -1;

    std::string currentSection;
    std::string currentUsername;

    std::string line;
    while(std::getline(in, line))
    {
        if(!line.empty() && line.back() == '\r')
            line.pop_back();

        if(line.empty() || line[0] == '#')
            continue;

        if(line[0] == '[')
        {
            std::string tag = line.substr(1, line.size() - 2);
            auto colon = tag.find(':');
            if(colon != std::string::npos)
            {
                currentSection  = tag.substr(0, colon);
                currentUsername = tag.substr(colon + 1);
            }
            else
            {
                currentSection  = tag;
                currentUsername.clear();
            }
            continue;
        }

        auto f = splitLine(line, '|');

        if(currentSection == "METADATA")
        {
            if(f.size() < 2) continue;
            int val = std::stoi(f[1]);
            if(f[0] == "food_id_gen")                metaFoodId          = val;
            else if(f[0] == "exercise_id_gen")        metaExerciseId      = val;
            else if(f[0] == "food_entry_id_gen")      metaFoodEntryId     = val;
            else if(f[0] == "exercise_entry_id_gen")  metaExerciseEntryId = val;
            else if(f[0] == "user_id_gen")            metaUserId          = val;
        }
        else if(currentSection == "FOOD")
        {
            if(f.size() < 6) continue;
            int s8Id  = std::stoi(f[0]);
            int s8Cal = std::stoi(f[2]);
            int s8Pro = std::stoi(f[3]);
            int s8Car = std::stoi(f[4]);
            int s8Fat = std::stoi(f[5]);
            system.foods.emplace(f[1], Food(s8Id, f[1], s8Cal, s8Pro, s8Car, s8Fat));
        }
        else if(currentSection == "EXERCISE")
        {
            if(f.size() < 4) continue;
            int    s8Id          = std::stoi(f[0]);
            double f32CalPerHour = std::stod(f[2]);
            system.exercises.emplace(
                f[1], Exercise(s8Id, f[1], f32CalPerHour, strToMuscleGroup(f[3])));
        }
        else if(currentSection == "USER" && currentUsername == "TRAINEE")
        {
            if(f.size() < 8) continue;
            int    s8Id      = std::stoi(f[0]);
            int    s8Age     = std::stoi(f[3]);
            double f32Weight = std::stod(f[4]);
            double f32Height = std::stod(f[5]);
            UserProfile prof(s8Age, f32Weight, f32Height,
                             strToGender(f[6]), strToActivityLevel(f[7]));
            system.users[f[1]] = std::make_unique<Trainee>(s8Id, f[1], f[2], prof);
            currentUsername = f[1];
        }
        else if(currentSection == "USER" && currentUsername == "ADMIN")
        {
            if(f.size() < 4) continue;
            int s8Id = std::stoi(f[0]);
            system.users[f[1]] =
                std::make_unique<Admin>(s8Id, f[1], f[2], UserProfile{}, f[3]);
        }
        else if(currentSection == "FOOD_DIARY")
        {
            if(f.size() < 6) continue;
            auto it = system.users.find(currentUsername);
            if(it == system.users.end()) continue;
            Trainee* p_trainee = dynamic_cast<Trainee*>(it->second.get());
            if(!p_trainee) continue;

            Food* p_food = system.findFood(f[1]);
            if(!p_food)
            {
                std::cerr << "Load warning: food '" << f[1] << "' not found, skipping entry.\n";
                continue;
            }
            double f32Qty = std::stod(f[2]);
            Date date(std::stoi(f[3]), std::stoi(f[4]), std::stoi(f[5]));
            p_trainee->addFoodEntry(FoodEntry(*p_food, f32Qty, date));
        }
        else if(currentSection == "EXERCISE_DIARY")
        {
            if(f.size() < 6) continue;
            auto it = system.users.find(currentUsername);
            if(it == system.users.end()) continue;
            Trainee* p_trainee = dynamic_cast<Trainee*>(it->second.get());
            if(!p_trainee) continue;

            Exercise* p_exercise = system.findExercise(f[1]);
            if(!p_exercise)
            {
                std::cerr << "Load warning: exercise '" << f[1] << "' not found, skipping entry.\n";
                continue;
            }
            int s8Duration = std::stoi(f[2]);
            Date date(std::stoi(f[3]), std::stoi(f[4]), std::stoi(f[5]));
            p_trainee->addExerciseEntry(ExerciseEntry(*p_exercise, s8Duration, date));
        }
        else if(currentSection == "GOALS")
        {
            if(f.size() < 9) continue;
            auto it = system.users.find(currentUsername);
            if(it == system.users.end()) continue;
            Trainee* p_trainee = dynamic_cast<Trainee*>(it->second.get());
            if(!p_trainee) continue;

            GoalType gt      = strToGoalType(f[0]);
            double f32Target = std::stod(f[1]);
            Date startDate(std::stoi(f[2]), std::stoi(f[3]), std::stoi(f[4]));
            Date deadline(std::stoi(f[5]), std::stoi(f[6]), std::stoi(f[7]));
            FitnessGoal goal(gt, f32Target, startDate, deadline);
            if(f[8] == "1")
                goal.completeGoal();
            p_trainee->addGoal(goal);
        }
        else if(currentSection == "FAVORITES")
        {
            auto it = system.users.find(currentUsername);
            if(it == system.users.end()) continue;
            Trainee* p_trainee = dynamic_cast<Trainee*>(it->second.get());
            if(!p_trainee) continue;

            Exercise* p_exercise = system.findExercise(line);
            if(!p_exercise)
            {
                std::cerr << "Load warning: exercise '" << line << "' not found, skipping favorite.\n";
                continue;
            }
            p_trainee->addFavoriteExercise(*p_exercise);
        }
    }

    // Apply saved id generators now that all objects have been created.
    if(metaFoodId          >= 0) Food::s8IdGenerator          = metaFoodId;
    if(metaExerciseId      >= 0) Exercise::s8IdGenerator      = metaExerciseId;
    if(metaFoodEntryId     >= 0) FoodEntry::s8IdGenerator     = metaFoodEntryId;
    if(metaExerciseEntryId >= 0) ExerciseEntry::s8IdGenerator = metaExerciseEntryId;
    if(metaUserId          >= 0) User::s8IdGenerator          = metaUserId;

    std::cout << "Loaded from " << filename << "\n";
}
