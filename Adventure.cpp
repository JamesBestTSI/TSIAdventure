#include <iostream> // This includes all code/functions for input/output of data streams
#include <conio.h>
#include <string>   // This allows us to work with string types (Lots of characters joined together such as words)
#include <stdexcept>// This allows us to use try/catch
#include "Source/Characters/CharactersController.cpp"
#include "Source/Characters/Character.cpp"
#include "Source/Characters/CharacterFaces.cpp"
#include "Source/System/CoreFunctions.cpp"
#include "Source/Maps/World.cpp"

void SetupCharacters(CharactersController &characterController);
void CheckForMovement(char button, World &gameWorld,  Character &player );
void UpdateHunger(Character &player);
void CreateMap(CoreFunctions core, World &gameWorld);
void ProcessRoom(CoreFunctions core, std::string roomName);

void ProcessSmallHouse(CoreFunctions core);



/// <summary>
/// The start of the main game loop.
/// </summary>
/// <returns></returns>
int main()
{
    std::cout << "It is advised to run the EXE and not in terminal\nPartly so you can fullscreen the window,\nbut also because some characters will not display in terminal.\nPress any key to continue..." <<std::endl;
    getch();


    // Set up instances
    CoreFunctions core = CoreFunctions();
    World gameWorld = World();
    CharacterFaces faces = CharacterFaces();
    CharactersController characterController = CharactersController();
    CreateMap(core,gameWorld);
    system("cls");

    // Create players character
    Character player = Character("Player", 10,10,2,2);
    player.DisplayCharacterFace();
    player.ChangeEyes();
    player.ChangeMouth();
    std::cout << "Please Enter Your Name: ";
    player.SetName(core.GetString());

    // Create the world map
    SetupCharacters(characterController);
    
    bool gameIsRunning = true;
    int fingers=10;

    while (gameIsRunning){
        bool hunger = false;
        system("cls");
        World::Room currentRoom = gameWorld.worldMap[ gameWorld.playerPos[1]*gameWorld.worldWidth+gameWorld.playerPos[0]];
        //std::string roomName =  gameWorld.worldMap[ gameWorld.playerPos[1]*gameWorld.worldWidth+gameWorld.playerPos[0]].Name;
        UpdateHunger(player);

        // Common Display
        player.DisplayCharacterStats();
        player.DisplayCharacterInventory();
        
        std::cout << "\n------------------------" << std::endl;
        gameWorld.DisplayWorldMap();
        std::cout << "\n-----------Location-------------" << std::endl;
        std::cout << player.characterData.Name << " is stood near a " << currentRoom.Name<< std::endl;
        std::cout << "Description: " << currentRoom.Description << std::endl;
        //gameWorld.DescriptionOfRoomAt(gameWorld.playerPos[0],gameWorld.playerPos[1]);
        std::cout << "\n------------------------\n" << std::endl;
        std::cout << "\nMove with W,A,S,D" << std::endl;

        // Show info if starving 
        if (player.characterData.Starved)
        {std::cout << "\nYou started to starve, so you decided to chew off a finger\nOnly " << player.characterData.fingers <<" remaining!\n"; player.characterData.Starved=false;}

        ProcessRoom(core, currentRoom.Name);
        
        std::cout <<"Move:";
        char button = getch();
        CheckForMovement(button, gameWorld,player);
        
    }
}

void CreateMap(CoreFunctions core, World &gameWorld){
    bool worldCreated=false;
    while (!worldCreated){
        system("cls");
        std::cout << "Please enter width of world (EG 30): ";
        int xsize = core.GetInt();
        std::cout << "Please enter height of world(EG 10): ";
        int ysize = core.GetInt();

        

        bool worldReady=false;
        gameWorld.playerPos[0]=0;
        gameWorld.playerPos[1]=0;
        while(!worldReady){
            system("cls");
            gameWorld.SetWorldSize(xsize, ysize);
            std::cout << "-";
            gameWorld.CreateWorldMap();
            std::cout << "-";
            gameWorld.CreateImportantRooms();
            std::cout << "-";
            gameWorld.ScatterImportantRooms();
            std::cout << "-";    
            gameWorld.PlacePlayerInRoom(0,0);
            gameWorld.UpdateRoomsData();
            std::cout << "-" << std::endl;
            gameWorld.CreatePaths();
            gameWorld.DisplayWorldMap();

            std::cout << "Press 'n' for new map 's' for new size, or any other key to continue: ";
            char btn = getch();
            switch(btn){
                case 's':{
                    worldReady=true;
                    break;
                } 
                case 'n':{
                    break;
                }
                default:{ 
                    worldCreated = true;
                    worldReady=true;
                    break;
                }
            }
        }
    }
};

void SetupCharacters(CharactersController &characterController)
{
    characterController.gameCharacters[0] = Character("The Drunk", 10, 15, 1, 1);
    characterController.gameCharacters[1] = Character("The Shopkeep", 350, 10, 25, 15);
    characterController.gameCharacters[2] = Character("The Necromancer", 100, 666, 2, 35);
    characterController.gameCharacters[3] = Character("The Merman", 800, 500, 25, 25);
    characterController.gameCharacters[4] = Character("The Dragon", 9999, 9999, 99, 99);
    characterController.gameCharacters[5] = Character("The King", 500, 0, 15, 10);
};

void CheckForMovement(char button, World &gameWorld,  Character &player){
    switch(button){
            case 'w':{
                if (gameWorld.worldMap[gameWorld.playerIndex].Up!=NULL){
                    if(gameWorld.worldMap[gameWorld.playerIndex].Up->usable){
                        player.characterData.Hunger++;
                        gameWorld.PlacePlayerInRoom(gameWorld.playerPos[0],gameWorld.playerPos[1]-1);
                    }
                }
                else{
                    gameWorld.ExpandWorldMap(World::directions::Up);
                    gameWorld.PlacePlayerInRoom(gameWorld.playerPos[0],gameWorld.playerPos[1]+1);
                    gameWorld.PlacePlayerInRoom(gameWorld.playerPos[0],gameWorld.playerPos[1]);
                }
                break;
            }
            case 'a':{
                if (gameWorld.worldMap[gameWorld.playerIndex].Left!=NULL){
                    if(gameWorld.worldMap[gameWorld.playerIndex].Left->usable){
                        player.characterData.Hunger++;
                        gameWorld.PlacePlayerInRoom(gameWorld.playerPos[0]-1,gameWorld.playerPos[1]);
                    }
                }
                else{
                    gameWorld.ExpandWorldMap(World::directions::Left);
                    gameWorld.PlacePlayerInRoom(gameWorld.playerPos[0]+1,gameWorld.playerPos[1]);
                    gameWorld.PlacePlayerInRoom(gameWorld.playerPos[0],gameWorld.playerPos[1]);
                }
                break;
            }
            case 's':{
                if (gameWorld.worldMap[gameWorld.playerIndex].Down!=NULL){
                    if(gameWorld.worldMap[gameWorld.playerIndex].Down->usable){
                        player.characterData.Hunger++;
                        gameWorld.PlacePlayerInRoom(gameWorld.playerPos[0],gameWorld.playerPos[1]+1);
                    }
                }
                else{
                    gameWorld.ExpandWorldMap(World::directions::Down);
                    gameWorld.PlacePlayerInRoom(gameWorld.playerPos[0],gameWorld.playerPos[1]);
                }
                break;
            }
            case 'd':{
                if (gameWorld.worldMap[gameWorld.playerIndex].Right!=NULL){
                    if(gameWorld.worldMap[gameWorld.playerIndex].Right->usable){
                        player.characterData.Hunger++;
                        gameWorld.PlacePlayerInRoom(gameWorld.playerPos[0]+1,gameWorld.playerPos[1]);
                    }
                }
                else{
                    gameWorld.ExpandWorldMap(World::directions::Right);
                    gameWorld.PlacePlayerInRoom(gameWorld.playerPos[0],gameWorld.playerPos[1]);
                }
                break;
            }
        }
}

void UpdateHunger(Character &player){
    if (player.characterData.Hunger>30&& player.characterData.fingers>0){   
            player.characterData.Starved=true;
            player.characterData.fingers--;
            player.characterData.HPCurrent--;
            player.characterData.Hunger-=10;
        }
};

void ProcessRoom(CoreFunctions core, std::string roomName){
    if(roomName == "Small House"){
        ProcessSmallHouse(core);
    }
    else if(roomName == "Small House"){
    }
    else if(roomName == "Swamp"){
    }
    else if(roomName == "Wood Cabin"){
    }
    else if(roomName == "Large Tree"){
    }
    else if(roomName == "Graveyard"){
    }
    else if(roomName == "Lake"){
    }
    else if(roomName == "Cave"){
    }
    else if(roomName == "Castle"){
    }
    else if(roomName == "Empty Room"){
    }
    else if(roomName == "BLOCKED"){
    }
    else {
    }
};


void ProcessSmallHouse(CoreFunctions core){
    std::cout << "1. Take a small nap.\n2.Have a look around.\n>" ;
     int ans = core.GetInt();
        
        std::cin.ignore();
        switch(ans){
            case 1:{
                std::cout <<"\nYou take a small nap and feel healthier, although slightly more hungry."<< std::endl;
                break;
            }
            case 2:{
                std::cout <<"\nYou take a look around and find nothing of interest."<< std::endl;
                break;
            }
            default:{
                std::cout <<"\nYou don't sem to want to do either of the two options that come to mind, and so just stand there for a while looking dumb."<< std::endl;
            }
        }
};