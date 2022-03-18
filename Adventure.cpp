#include <iostream> // This includes all code/functions for input/output of data streams
#include <string>   // This allows us to work with string types (Lots of characters joined together such as words)
#include <stdexcept>// This allows us to use try/catch

const char HIDDENBLOCK = (char)219;
const char UD = (char)186;
const char LR = (char)205;
const char directions[9] = { (char)201,(char)203,(char)181,
                              (char)204,(char)206,(char)185,
                              (char)200,(char)202,(char)188 };



/// <summary>
/// Gets a number from the user.
///     Reads the data from the console, 
///     Checks that it is a actual valid number, 
///     Then returns that value.
/// </summary>
/// <returns>Number entered by user</returns>
int GetInt(){
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
std::string GetString(){
    std::string consoleInput;
    std::getline(std::cin, consoleInput);
    return consoleInput;
}

/// <summary>
/// Gets the first Char from the user.
/// </summary>
/// <returns>consoleInput[0]</returns>
char GetChar()
{
    std::string consoleInput = GetString();
    return consoleInput[0];
}

struct Item {
    std::string Name = "Empty";
    std::string Description = "Empty";
};

struct Inventory {
    Item items[10];
};


struct Room {
    std::string Name;
    Item items[10];
};


struct Map {
    Room rooms[5][5];
};


struct Character {
    std::string Name = "Blank";
    int HPMax = 0;
    int MPMax = 0;
    int HPCurrent = 0;
    int MPCurrent = 0;
    int Str = 0;
    int Int = 0;
    Inventory inventory;
};


void DisplayCharacterInventory(Character character) {
    int slotNumber = 0;
    std::cout << "\n----Inventory----" << std::endl;
    for (Item item : character.inventory.items) {
        std::cout << "Slot " << slotNumber << " - " << item.Name << "\n  -" << item.Description << std::endl;
    }
}

void DisplayCharacterStats(Character character) {

    std::cout << "        ,,,\n       (o o)\n----oOO--()--OOo----" << std::endl;
    std::cout << "Name: " << character.Name << std::endl;
    std::cout << "HP: " << character.HPCurrent << "/" << character.HPMax << std::endl;
    std::cout << "HP: " << character.MPCurrent << "/" << character.MPMax << std::endl;
    std::cout << "Int: " << character.Int << std::endl;
    std::cout << "Str: " << character.Str << std::endl;
    //DisplayCharacterInventory(character);
}



/// <summary>
/// The start of the main game loop.
/// </summary>
/// <returns></returns>
int main()
{
    //system("cls");
    Character player;

    for (int index = 0; index < 255; index++) {
        std::cout << "Index " << index << " " << (char)index << std::endl;
    }



    std::cout << "Please Enter Your Name: ";
    player.Name = "James";//GetString();
    player.HPMax = 100;
    player.HPCurrent = 100;
    player.MPMax = 100;
    player.MPCurrent = 100;
    player.Str = 5;
    player.Int = 5;


    system("cls");
    DisplayCharacterStats(player);
















    std::cout << "Enter number: ";
    int num = GetInt();
    std::cout << "Enter String: ";
    std::string text = GetString();
    std::cout << "Enter Character: ";
    char letter = GetChar();
}
