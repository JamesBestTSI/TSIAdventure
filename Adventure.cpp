#include <iostream> // This includes all code/functions for input/output of data streams
#include <conio.h>
#include <string>   // This allows us to work with string types (Lots of characters joined together such as words)
#include <stdexcept>// This allows us to use try/catch
#include "Adventure.h"
#include "Source/Characters/Character.cpp"
#include "Source/Characters/CharactersController.cpp"
#include "Source/Characters/CharacterFaces.cpp"
#include "Source/System/CoreFunctions.cpp"
#include "Source/Maps/World.cpp"

void SetupCharacters(CharactersController &characterController);
void CheckForMovement(char button, World &gameWorld,  Character &player );
void UpdateHunger(Character &player);
void CreateMap(CoreFunctions core, World &gameWorld);
void ProcessRoom(CoreFunctions core, World::Room &room);
void DisplayGameWorld(World &gameWorld);

bool gameIsRunning = true;
bool hasLadder = false;
bool hasEgg = false;
bool hasScroll = false;
bool hasStaff = false;
bool hasMerman = false;
bool hasSword = false;
bool hasCrown = false;

Character player;
World gameWorld;
/// <summary>
/// The start of the main game loop.
/// </summary>
/// <returns></returns>
int main()
{
    std::cout << "#######################################################################################" << std::endl;
    for (int loop = 0; loop < 40;loop++){std::cout << "#                                                                                     #" << std::endl;}
    std::cout << "#######################################################################################" << std::endl;

    //std::cout << "Currently: Level ups work, EXP gain, 2 different Fights, house, sleeping, wood cabin, bridges, expanding land, character customization, cooking at campfires all complete." << std::endl;
    //std::cout << "TODO: Give items, Main Character dialogues, Other areas, Game Over on 0 health" << std::endl;
    std::cout << " - It is advised to run the EXE and not in terminal\n - Make sure you can see the whole of the box above.\nPress any key to continue..." << std::endl;
    getch();

    // Set up instances
    CoreFunctions core = CoreFunctions();
    //gameWorld = World();
    CharacterFaces faces = CharacterFaces();
    CharactersController characterController = CharactersController();
    CreateMap(core,gameWorld);
    system("cls");

    // Create players character
    player = Character("Player", 50, 30, 5, 5);
    std::cout << "#############################" << std::endl;
    std::cout << "#  Character Customization  #" << std::endl;
    std::cout << "#############################" << std::endl;
    player.DisplayCharacterFace();
    player.ChangeEyes();
    player.ChangeMouth();
    std::cin.clear();
    std::cin.ignore();
    std::cout << "Please Enter Your Name: ";
    player.SetName(core.GetString());

    // Create the world map
    SetupCharacters(characterController);
    int fingers=10;

    while (gameIsRunning){
        bool hunger = false;
        DisplayGameWorld(gameWorld);
        std::cout << "\nMove with W,A,S,D" << std::endl;

        // Show info if starving 
        if (player.characterData.Starved)
        { 
            if (player.characterData.fingers>0)
            { 
                std::cout << "\nYou started to starve, so you decided to chew off a finger\nOnly " << player.characterData.fingers <<" remaining!\n";
                player.characterData.Starved=false;
            }
            else
            {
                std::cout << "\nYou are starving, and with no finders left to eat youhave no idea what to do.";
            }            
        }

        World::Room *currentRoom = &gameWorld.worldMap[gameWorld.playerPos[1] * gameWorld.worldWidth + gameWorld.playerPos[0]];
        ProcessRoom(core, *currentRoom);
        
        std::cout <<"Move:";
        char button = getch();
        CheckForMovement(button, gameWorld,player);        
    }
}

void CreateMap(CoreFunctions core, World &gameWorld){
    bool worldCreated=false;
    while (!worldCreated){
        system("cls");
        std::cout << "Lets create the world we will play in\n\nLarger worlds will be much harder to get to new locations.\n" << std::endl;
        std::cout << "World Width" << std::endl;
        int xsize = core.GetIntMinMax(5, 100);
        int minValue = (10/xsize)+2;
        std::cout << "World Height: " << std::endl;
        int ysize = core.GetIntMinMax(minValue, 40);

        bool worldReady=false;
        gameWorld.playerPos[0]=0;
        gameWorld.playerPos[1]=0;
        while(!worldReady){
            system("cls");
            gameWorld.SetWorldSize(xsize, ysize);
            std::cout << "\n---- ";
            gameWorld.CreateWorldMap();
            std::cout << "\n---- ";
            gameWorld.CreateImportantRooms();
            std::cout << "\n---- ";
            gameWorld.ScatterImportantRooms();
            std::cout << "\n---- ";    
            gameWorld.PlacePlayerInRoom(0,0);
            gameWorld.UpdateRoomsData();
            gameWorld.CreatePaths();
            gameWorld.DisplayWorldMap();

            std::cout << "Press 'n' for new map 's' for new size, or any other key to continue: ";
            char btn = getch();
            switch(btn){
                case 's':
        {
            worldReady = true;
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

void Fight(CoreFunctions core, Character &badGuy, bool playerStarts)
{
    bool starting = playerStarts;
    std::mt19937 gen(time(0));
    std::uniform_int_distribution<> distr(0, 100);
    bool fighting = true;
    std::cout << "The battle begins.\n Press any key to continue..." << std::endl;
    getch();
    badGuy.DisplayCharacterStats();
    while(fighting){
        system("cls");
        badGuy.DisplayCharacterStats();
        player.DisplayCharacterFace();
        player.DisplayCharacterStats();
        if (starting)
        {
            std::cout << "1. Attack\n2. Flee" << std::endl;
            char ans = getch();
           
            switch (ans)
            {
                case '1':
                {
                    std::cout << "You attack the "<< badGuy.characterData.Name << " and deal "<< player.characterData.Str/2 << " damage." << std::endl;
                    badGuy.characterData.HPCurrent -= player.characterData.Str / 2;
                    if (badGuy.characterData.HPCurrent<=0){
                        std::cout << "The fight is over and you managed to live." << std::endl;
                        fighting = false;
                        player.GiveEXP(badGuy.characterData.EXP);
                        if (badGuy.characterData.Name == "Bunny"){
                            player.GiveItem(Rabbit);
                        }
                        return;
                    }
                    break;
                }
                case '2':
                {
                    std::cout << "You try to flee...";
                    int chance = distr(gen);
                    if (chance>40)
                    {
                        std::cout << "It was successful"<<std::endl;
                        return;
                    }
                    std::cout << "It Failed!" << std::endl;
                }
                default:
                {
                }
            }
        }
        starting = true;
        // Badguy turn

        std::cout << badGuy.characterData.Name << " attacks for " << badGuy.characterData.Str / 2 << " damage." << std::endl;
        player.TakeDamage(badGuy.characterData.Str / 2);
        std::cout << "Press any key to continue..";
        getch();
    }

    return;
};

void ProcessGrassland(CoreFunctions core, World::Room &room){
    // Random chance of fight
    std::mt19937 gen(time(0));
    std::uniform_int_distribution<> distr(0, 100);
    int chance = distr(gen);
    // Use chance to battle
    if (chance > 80 && chance < 95)
    {
        Character badGuy;
        badGuy.SetName("Bunny");
        badGuy.characterData.HPCurrent = 5;
        badGuy.characterData.HPMax = 5;
        badGuy.characterData.Str = 2;
        badGuy.characterData.EXP = 3;
        // Fight
        std::cout << "You stumble across a rabbit, and it looks pretty tasty.\n1. Kill Rabbit\n2. Leave it be.\n";
        int ans = core.GetInt();
        switch (ans)
        {
        case 1:
        {
            // fight
            Fight(core, badGuy, true);
            break;
        }
        case 2:
        {
            // flee
            std::cout << "You leave it be and continue on your way." << std::endl;
            break;
        }
        default:
        {
            std::cout << "Not knowing what to do, you stand there just looking at it for a while.\nAt which point it decides to attack you." << std::endl;
            Fight(core, badGuy, false);
        }
        }
    }
    else if (chance >= 95)
    {
        Character badGuy;
        badGuy.SetName("Goblin");
        badGuy.characterData.HPCurrent = 20;
        badGuy.characterData.HPMax = 20;
        badGuy.characterData.Str = 6;
        badGuy.characterData.EXP = 6;
        // Fight
        std::cout << "You stumble across a goblin, and it looks angry.\n1. Kill Goblin\n2. Try to run.\n";
        int ans = core.GetInt();
        switch (ans)
        {
        case 1:
        {
            // fight
            Fight(core, badGuy, true);
            break;
        }
        case 2:
        {
            // flee
            chance = distr(gen);
            if (chance>30)
            {
                std::cout << "You manage to get away okay!" << std::endl;
                return;
            }
            Fight(core, badGuy, true);
            break;
        }
        default:
        {
            std::cout << "Not knowing what to do, you stand there just looking at it for a while.\nAt which point it decides to attack you." << std::endl;
            Fight(core, badGuy, false);
        }
        }
    }
};

void ProcessSmallHouse(CoreFunctions core){
    std::cout << "1. Take a small nap.\n2. Have a look around.\n>" ;
     int ans = core.GetInt();
    switch(ans){
        case 1:{
            std::cout <<"\nYou take a small nap and feel healthier, although slightly more hungry."<< std::endl;
            player.characterData.HPCurrent = player.characterData.HPMax;
            player.EditHungerBy(5);
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

void ProcessSwamp(CoreFunctions core, World::Room &room){
    if (!hasStaff)
    {
        std::cout << "You see a merman angrily hunting around for his staff." << std::endl;
    }
    else
    {
        if (!hasMerman)
        {
            std::cout << "You hand the merman his stolen staff and in thanks he points in a direction and all you hear is the word -Lake-" << std::endl;
            hasMerman = true;
        }
    }
};

void ProcessWoodCabin(CoreFunctions core, World::Room &room){
    std::cout << "You stumble across a small wood cabin.\nWhat would you like to do?" << std::endl;
    std::cout << "1. Inspect." << std::endl
              << "2. Leave." << std::endl;
    int ans = core.GetInt();

    switch (ans)
    {
        case 1:
        {
            DisplayGameWorld(gameWorld);
            std::cout << "\nYou take a good look at the cabin and notice a door and a window." << std::endl;
            std::cout << "1. Inspect Door." << std::endl
                    << "2. Inspect Window." << std::endl
                    << "3. Leave." << std::endl;

            int ans = core.GetInt();
            switch (ans){
                case 1: // Inspect Door
                {
                    if (room.Inspect == 0) // Door is shut
                    {
                        DisplayGameWorld(gameWorld);
                        std::cout << "\nYou walk over to the door and try to open it, but it seems pretty tightly shut.\nWith enough strength you might be able to open it." << std::endl;
                        std::cout << "1. Try to break down the Door." << std::endl
                                << "2. Inspect the Window." << std::endl
                                << "3. Leave." << std::endl;

                        int ans = core.GetInt();
                        switch(ans)
                        {
                            case 1:
                            {   // Break down the door
                                if (player.characterData.Str > 6)
                                {
                                    DisplayGameWorld(gameWorld);
                                    std::cout << "\nYou throw yourself against the door in hopes that it will burst open.\nThankfully you have gained enough strength during your travels and break down the door with no issues." << std::endl;
                                    room.Inspect++;
                                }
                                else
                                {
                                    DisplayGameWorld(gameWorld);
                                    std::cout << "\nYou throw yourself against the door in hopes that it will burst open.\nHowever as you slam into the door, a huge pain shoots through your shoulder.\nIt seems you aren't strong enough." << std::endl;
                                    player.TakeDamage(1);
                                    return;
                                }
                                break;
                            }
                            case 3:{return;}
                            case 2: // Inspect the window
                            {break;}
                            default:
                            {
                                DisplayGameWorld(gameWorld);
                                std::cout << "\nAs smart as you are, you seem to have no idea what you want to do and so just walk away." << std::endl;
                                return;
                            }
                        }
                    }
                    if (room.Inspect==1) // Door is open
                    {
                        DisplayGameWorld(gameWorld);
                        std::cout << "\nWith the door now open you take a look inside the cabin." << std::endl;
                        std::cout << "Inside you spot a mixture of junk, but one thing catches your eye.\nA what looks like master craft ladder that extends is sat up against the far wall."<<std::endl;
                        std::cout << "1. Take the ladder\n2. Leave the cabin." << std::endl;
                        int ans = core.GetInt();
                        switch(ans)
                        {
                        case 1:
                        {
                            DisplayGameWorld(gameWorld);
                            player.GiveItem(Ladder);
                            room.Inspect++;
                            return;
                        }
                        case 2:
                        {
                            return;
                        }
                        default:
                        {
                            DisplayGameWorld(gameWorld);
                            std::cout << "\nAs smart as you are, you seem to have no idea what you want to do and so just walk away." << std::endl;
                            return;
                        }
                        }
                    }
                    else{
                        std::cout << "\nWith the door now open you take a look inside the cabin." << std::endl;
                        std::cout << "There seems to be nothing of interest here, so you leave." << std::endl;
                        return;
                    }
                }
                case 2: // Inspect Window
                {
                    DisplayGameWorld(gameWorld);
                    std::cout << "\nYou look through the window and spot a ladder inside the cabin.\nSadly the window is blocked by all manor of things, and is too small the enter." << std::endl;
                    break;
                }
                case 3:{return;
                } // Leave
                default:
                {
                    DisplayGameWorld(gameWorld);
                    std::cout << "\nAs smart as you are, you seem to have no idea what you want to do and so just walk away." << std::endl;
                    return;
                }
            }
            break;
        }
        case 2:
        {
            DisplayGameWorld(gameWorld);
            std::cout << "\nYou decide that you care not for the cabin and leave." << std::endl;
            break;
        }
        default:
        {
            DisplayGameWorld(gameWorld);
            std::cout << "\nAs smart as you are, you seem to have no idea what you want to do and so just walk away." << std::endl;
            return;
        }
    }
};

void ProcessLargeTree(CoreFunctions core, World::Room &room){
    // Random chance of fight

    if (!hasLadder){
        for (int index = 0; index < 10; index++)
        {
            if (player.characterData.inventory.itemList.items[index].Name == "Ladder")
            {
                hasLadder = true;
            }
        }
        if (!hasLadder){
            std::cout << "Looks like you could climb this" << std::endl;
        }
    }

    if (hasLadder && !hasEgg){
        std::cout << "You use the ladder to climb the tree.\nAt the top of the tree you find a huge egg." << std::endl;
        hasEgg = true;
    }
};

void ProcessGraveyard(CoreFunctions core, World::Room &room){
    if (!hasScroll)
    {
        std::cout << "A nasty necromancer with a stolen staff is furiously hunting through a pile of scrolls." << std::endl;
    }
    else
    {
        if (!hasStaff)
        {
            std::cout << "The necromancer spots that you have a scroll and trades you it for his staff." << std::endl;
            hasStaff = true;
        }
    }
};

void ProcessLake(CoreFunctions core, World::Room &room){
    if (!hasMerman)
    {
        std::cout << "Something seems to be sparkleing at the bottom of the lake but it's too deep to swim down to." << std::endl;
    }
    else
    {
        if (!hasSword)
        {
            std::cout << "You find the merman floating in the lake, he swims down to the bottom and brings back a golden sword." << std::endl;
            hasSword = true;
        }
    }
};

void ProcessCave(CoreFunctions core, World::Room &room){
    if (!hasSword)
    {
        std::cout << "Entering the cave you spot a dragon protecting his gold, and decide to retreat." << std::endl;
    }
    else
    {
        if (!hasCrown)
        {
            std::cout << "You run headfirst into the cave with a golden sword in hand and slay the dragon hording it's gold. As a reward you pick up a golden crown." << std::endl;
            hasCrown = true;
        }
    }
};

void ProcessCastle(CoreFunctions core, World::Room &room){
    if (!hasCrown)
    {
        std::cout << "Visiting the castle you meet with a king, who explains his crown was stolen by a Dragon hwo hides in a cave." << std::endl;
    }
    else
    {
        if (gameIsRunning)
        {
            std::cout << "You pass the king his crown and he thanks you.\n\n\n it seems your adventure ends here." << std::endl;
            gameIsRunning = false;
        }
    }
};

void ProcessCampfire(CoreFunctions core){
    std::cout << "Nice warm campfire." << std::endl;
    bool hasFood = false;
    int foodIndex = 0;
    for (int index = 0; index<10;index++){
        if (player.characterData.inventory.itemList.items[index].Name == "Rabbit")
        {
            hasFood = true;
            foodIndex = index;
        }
    }

    if (hasFood){
        std::cout << "You could cook food here if you wanted..\n1. Cook Food\n2. Ignore" << std::endl;
        int ans = core.GetInt();
        switch (ans){
            case 1:{
                std::cout << "You go ahead and cook some food...\nIt tastes alright, but not the best." << std::endl;
                player.EditHungerBy(-15);
                player.TakeDamage(-5);
                player.characterData.inventory.itemList.items[foodIndex].amount--;
                if (player.characterData.inventory.itemList.items[foodIndex].amount == 0){
                    player.characterData.inventory.ClearItem(foodIndex);
                }
                break;
            }
            default:
            {
                std::cout << "You decide not to bother cooking food just yet." << std::endl;
            }
        }
    }
    else
    {
        std::cout << "You could cook food here if you had any.\nBut for now you just enjoy the warm glow." << std::endl;
    }
};

void ProcessShop(CoreFunctions core, World::Room &room){
    // Random chance of fight
    if (!hasEgg){
        std::cout << "You see a shop keeper who seems willing to trade a magic scroll for a rare egg." << std::endl;
    }
    else{
        if (!hasScroll){
            std::cout << "The shop keeper happily trades your edd for his scroll." << std::endl;
            hasScroll = true;
        }
    }
};

void ProcessRoom(CoreFunctions core, World::Room &room)
{
    switch (Adventure::EnumFromLocationName(room.Name))
    {
    case Blocked:
        // Process blocked room
        break;
    case EmptyRoom:
        // Process empty room
        break;
    case Grassland:
        ProcessGrassland(core, room);
        break;
    case SmallHouse:
        ProcessSmallHouse(core);
        break;
    case Swamp:
        ProcessSwamp(core, room);
        break;
    case WoodCabin:
        ProcessWoodCabin(core, room);
        break;
    case LargeTree:
        ProcessLargeTree(core, room);
        break;
    case Graveyard:
        ProcessGraveyard(core, room);
        break;
    case Lake:
        ProcessLake(core, room);
        break;
    case Cave:
        ProcessCave(core, room);
        break;
    case Castle:
        ProcessCastle(core, room);
        break;
    case Campfire:
        ProcessCampfire(core);
        break;
    case Shop:
        ProcessShop(core, room);
        break;
    }
};

void DisplayGameWorld(World &gameWorld){
    system("cls");
    World::Room *currentRoom = &gameWorld.worldMap[gameWorld.playerPos[1] * gameWorld.worldWidth + gameWorld.playerPos[0]];
    UpdateHunger(player);

    // Common Display
    player.DisplayCharacterFace();
    player.DisplayCharacterStats();
    player.DisplayCharacterInventory();

    std::cout << "\n------------------------" << std::endl;
    gameWorld.DisplayWorldMap();
    std::cout << "\n-----------Location-------------" << std::endl;
    std::cout << player.characterData.Name << " is stood near a " << currentRoom->Name << std::endl;
    std::cout << "Description: " << currentRoom->Description << std::endl;
    std::cout << "\n------------------------\n"
              << std::endl;
}