#include <iostream>
#include "CoreFunctions.h"
#include <string>

CoreFunctions::CoreFunctions(){};
CoreFunctions::~CoreFunctions(){};

/// <summary>
/// Gets a number from the user.
///     Reads the data from the console, 
///     Checks that it is a actual valid number, 
///     Then returns that value.
/// </summary>
/// <returns>Number entered by user</returns>
int CoreFunctions::GetInt(){
    while(true){
        int input;
        std::string consoleInput;
        std::cin  >> consoleInput;
        
        try{
            input = std::stoi(consoleInput);
            return input;
        }
        catch(...){
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