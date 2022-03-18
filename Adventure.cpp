#include <iostream> // This includes all code/functions for input/output of data streams
#include <string>   // This allows us to work with string types (Lots of characters joined together such as words)
#include <stdexcept>// This allows us to use try/catch
#include "Characters.cpp"
#include  "CoreFunctions.cpp"

const char HIDDENBLOCK = (char)219;
const char UD = (char)186;
const char LR = (char)205;
const char directions[9] = { (char)201,(char)203,(char)181,
                              (char)204,(char)206,(char)185,
                              (char)200,(char)202,(char)188 };



struct Room {
    std::string Name;
    Inventories::Item items[10];
};


struct Map {
    Room rooms[5][5];
};


/// <summary>
/// The start of the main game loop.
/// </summary>
/// <returns></returns>
int main()
{
    CoreFunctions core = CoreFunctions();
    Characters player = Characters();
    
    std::cout << "Please Enter Your Name: ";
    player.SetName(core.GetString());
    player.DisplayCharacterStats();
    player.DisplayCharacterInventory();



    system("cls");
    //Character player;

    //for (int index = 0; index < 255; index++) {
    //    std::cout << "Index " << index << " " << (char)index << std::endl;
    //



    std::cout << "Please Enter Your Name: ";
    /*
    player.Name = "James";//GetString();
    player.HPMax = 100;
    player.HPCurrent = 100;
    player.MPMax = 100;
    player.MPCurrent = 100;
    player.Str = 5;
    player.Int = 5;
*/

    system("cls");
    //DisplayCharacterStats(player);




}
