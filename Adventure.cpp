#include <iostream> // This includes all code/functions for input/output of data streams
#include <string>   // This allows us to work with string types (Lots of characters joined together such as words)
#include <stdexcept>// This allows us to use try/catch
#include "Source/Characters/CharactersController.cpp"
#include "Source/Characters/Character.cpp"
#include "Source/Characters/CharacterFaces.cpp"
#include "Source/System/CoreFunctions.cpp"
#include "Source/Maps/MapDesigner.cpp"


#include "Colour.h"

void SetupCharacters(CharactersController &characterController);


/// <summary>
/// The start of the main game loop.
/// </summary>
/// <returns></returns>
int main()
{
    // Set up instances
    system("cls");
    CoreFunctions core = CoreFunctions();
    MapDesigner maps = MapDesigner();
    CharacterFaces faces = CharacterFaces();
    CharactersController characterController = CharactersController();

    // Create players character
    Character player = Character("Player", 10,10,2,2);
    player.DisplayCharacterFace();
    player.ChangeEyes();
    player.ChangeMouth();
    std::cout << "Please Enter Your Name: ";
    player.SetName(core.GetString());
    system("cls");

    // Create the world map
    SetupCharacters(characterController);
    maps.CreateWorldMap();


    int playerX = 0;
    int playerY = 0;
    player.DisplayCharacterStats();

    maps.DrawWorldMap();

    std::cout << player.characterData.Name << " is at ";
    maps.NameOfRoomAt(playerX, playerY);

    std::cout << std::endl<< "Description: ";
    maps.DescriptionOfRoomAt(playerX, playerY);
    core.GetString();

    //for (int index = 0; index < 255; index++) {
    //std::cout << "Index " << index << " " << (char)index << std::endl;}
}

void SetupCharacters(CharactersController &characterController)
{
    characterController.gameCharacters[0] = Character("The Drunk", 10, 15, 1, 1);
    characterController.gameCharacters[1] = Character("The Shopkeep", 350, 10, 25, 15);
    characterController.gameCharacters[2] = Character("The Necromancer", 100, 666, 2, 35);
    characterController.gameCharacters[3] = Character("The Merman", 800, 500, 25, 25);
    characterController.gameCharacters[4] = Character("The Dragon", 9999, 9999, 99, 99);
    characterController.gameCharacters[5] = Character("The King", 500, 0, 15, 10);
}