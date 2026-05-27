#include "Admin.h"
#include <iostream>

Admin::Admin(const std::string& username, const std::string& password,
    UserProfile profile, const std::string& adminKey)
    : User(username, password, profile), adminKey(adminKey) {
}

Admin::Admin(int id, const std::string& username, const std::string& password,
    UserProfile profile, const std::string& adminKey)
    : User(id, username, password, profile), adminKey(adminKey)
{
}

const std::string& Admin::getAdminKey() const { return adminKey; }

void Admin::help() const {
    std::cout << "Available commands (Admin):\n"
        << "  block-user <username>\n"
        << "  add-food <name> <calories> <protein> <carbs> <fat>\n"
        << "  add-exercise <name> <cal_per_hour> <muscle-group>\n"
        << "  update-food <food-name> <new-calories>\n"
        << "  logout\n";
}