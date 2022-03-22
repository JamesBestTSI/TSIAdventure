#include <iostream>
#include "CoreFunctions.h"
#include <string>

// Constructor
CoreFunctions::CoreFunctions(){};
// De-constructor
CoreFunctions::~CoreFunctions(){};

/// <summary>
/// Gets a number from the user.
///     Reads the data from the console,
///     Checks that it is a actual valid number,
///     Then returns that value.
/// </summary>
/// <returns>Number entered by user</returns>
int CoreFunctions::GetInt()
{
    while (true)
    {
        int input = -1;
        std::string consoleInput;

        try
        {
            while (input < 0)
            {
                std::cin >> consoleInput;
                std::cin.ignore();
                input = std::stoi(consoleInput);
            }
            return input;
        }
        catch (...)
        {
            std::cout << "Thats not a number!" << std::endl;
        }
    }
}

/// <summary>
/// Gets a number from the user.
///     Reads the data from the console,
///     Checks that it is a actual valid number,
///     Then returns that value.
/// </summary>
/// <returns>Number entered by user</returns>
int CoreFunctions::GetIntMinMax(int min, int max)
{
    int input = -1;
    std::string consoleInput;
    while (true)
    {
        try
        {
            while (input < min || input > max)
            {
                std::cout << "Please enter a number between " << min << " and " << max << " :";
                std::cin >> consoleInput;
                std::cin.ignore();
                input = std::stoi(consoleInput);
            }
            return input;
        }
        catch (...)
        {
            std::cout << "Thats not a number!" << std::endl;
        }
    }
}

/// <summary>
/// Gets some string data from the user.
/// </summary>
/// <returns>The string they entered</returns>
std::string CoreFunctions::GetString(){
    std::string consoleInput;
    std::getline(std::cin, consoleInput);
    return consoleInput;
}


/// <summary>
/// Gets the first Char from the user.
/// </summary>
/// <returns>consoleInput[0]</returns>
char CoreFunctions::GetChar()
{
    std::string consoleInput = GetString();
    return consoleInput[0];
}