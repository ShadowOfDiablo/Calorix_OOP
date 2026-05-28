// Calorix.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "Calorix.h"
int main()
{
    Calorix system;
    std::cout << "Please select an option \n";
    std::cout << "1: login\n";
    std::cout << "2: register\n";
    std::cout << "3: load from file\n";
    std::string input = "";
    while(input != "end")
    {
        std::cin >> input;
        if(input == "1")
        {
            std::string user;
            std::string password;
            std::cout << "Enter your username and password:\n";
            std::cin >> user >> password;
            if(system.login(user,password) != nullptr)
            {
                std::cout << "Welcome back " << user << "!\n";
            }
            else
            {
                std::cout << "Wrong credentials\n";
            }
        }
        if(input == "2")
        {
            std::string user;
            std::string password;
            std::cout << "Enter your username and password:\n";
            std::cin >> user >> password;
            // system.registerTrainee()
        }
    }
    
    return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
