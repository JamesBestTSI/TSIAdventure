#include <iostream> // This includes all code/functions for input/output of data streams
#include <string>   // This allows us to work with string types (Lots of characters joined together such as words)
#include <stdexcept>// This allows us to use try/catch
#include "Source/Characters/CharactersController.cpp"
#include "Source/Characters/Character.cpp"
#include "Source/System/CoreFunctions.cpp"
#include "Source/Maps/MapDesigner.cpp"

const char HIDDENBLOCK = (char)219;
const char UD = (char)186;
const char LR = (char)205;
const char directions[9] = { (char)201,(char)203,(char)181,
                              (char)204,(char)206,(char)185,
                              (char)200,(char)202,(char)188 };






/// <summary>
/// The start of the main game loop.
/// </summary>
/// <returns></returns>
int main()
{
    system("cls");
    CoreFunctions core = CoreFunctions();
    MapDesigner maps = MapDesigner();
    CharactersController characterController = CharactersController();

    Character player = Character();


    Character drunk = Character("The Drunk",10,15,1,1);
    Character shopkeep = Character("The Shopkeep",350,10,25,15);
    Character necromancer = Character("The Necromancer",100,666,2,35);
    Character merman = Character("The Merman",800,500,25,25);
    Character dragon = Character("The Dragon",9999,9999,99,99);
    Character king = Character("The King",500,0,15,10);

    characterController.gameCharacters[0] = drunk;
    characterController.gameCharacters[1] = shopkeep;
    characterController.gameCharacters[2] = necromancer;
    characterController.gameCharacters[3] = merman;
    characterController.gameCharacters[4] = dragon;
    characterController.gameCharacters[5] = king;
    
    maps.CreateWorldMap();

    
    std::cout << "Please Enter Your Name: ";
    player.SetName(core.GetString());
    player.DisplayCharacterStats();
    //player.DisplayCharacterInventory();



    system("cls");
    //CharacterStats player;

    //for (int index = 0; index < 255; index++) {
    //    std::cout << "Index " << index << " " << (char)index << std::endl;}
}
