#include "World.h"
#include <iostream>
#include <random>

World::World(){};
World::~World(){};

void World::SetWorldSize(int x, int y ){
    std::cout <<"Setting World Size"<<std::endl;
    worldWidth = x; 
    worldHeight = y;
};

void World::CreateWorldMap(){
    std::cout <<"Creating World Map In Memory"<<std::endl;
    worldMap = new Room[worldHeight*worldWidth];
};

void World::CreateNewRoom(Room &room){
    room.mapIcon=176;
};

void World::CreateNewRoom(Room &room, std::string name, int icon, std::string description){
    room.Name = name;
    room.Description = description;
    room.mapIcon = icon;    
    std::cout << name<< " created as " << (char)icon<<std::endl;
};
void World::DisplayWorldMap(){
    for (int row = 0; row< worldHeight; row++){
        for (int col = 0; col< worldWidth; col++){
            if (worldMap[row*worldWidth+col].playerIsHere){std::cout << (char)153;}
            else{
                
                std::cout << (char)worldMap[row*worldWidth+col].mapIcon;
                }
        }
        std::cout << std::endl;
    }
};

void World::CreateImportantRooms(){
    std::cout <<"Creating Important Locations"<<std::endl;
    int rooms = LocationsLength; // This is here so we can expand the room count easier later if needed

    importantRooms = new Room [rooms];

    for (int index = 0; index < LocationsLength; index++){
        CreateNewRoom(importantRooms[index], Adventure::LocationNameFromEnum(LocationName(index)), Adventure::LocationIconFromEnum(LocationName(index)), Adventure::LocationDescriptionFromEnum(LocationName(index)));
    }
    /*
    CreateNewRoom(importantRooms[0],"Small House",127, "A small house seems an ideal place to rest.");
    CreateNewRoom(importantRooms[1],"Swamp",167, "...");
    CreateNewRoom(importantRooms[2],"Wood Cabin",35, "A broken down wooden cabin. Looks abandoned");
    CreateNewRoom(importantRooms[3],"Large Tree",20, "This tree is huge. Wonder what it's like up there...");
    CreateNewRoom(importantRooms[4],"Shop",36, "Looks like it might be possible to trade here.");
    CreateNewRoom(importantRooms[5],"Graveyard",241, "This place feels spooky.");
    CreateNewRoom(importantRooms[6],"Lake",229, "I hear all kinds of things get dumped in lakes.");
    CreateNewRoom(importantRooms[7],"Cave",182, "Seems dangerous.");
    CreateNewRoom(importantRooms[8],"Castle",222, "Looks like royalty lives here.");
    */
};

void World::ScatterImportantRooms(){
    std::cout <<"Scattering Important Locations Across The World"<<std::endl;

    // Create a randome number get for our X and Y pos
    //std::random_device rd;
    std::mt19937 gen(time(0));
    std::uniform_int_distribution<> distr(0, worldHeight - 1);
    std::uniform_int_distribution<> distr2(0, worldWidth - 1);

    // Create an array to store a room x and y pos
    int roomLocations[LocationsLength];

    for (int n = 0; n < LocationsLength; ++n)
    {
        int x = distr2(gen);   // Set the rooms x position
        int y = distr(gen);  // Set the rooms y position

        roomLocations[n] = y*worldWidth+x;

        // Check that this location hasn't been used
        for (int m = 0; m < n;m++)
        {
            if (roomLocations[m]==roomLocations[n]){
                n--;
            }
        }
    }

    // Place those rooms in the locations
    for (int roomIndex = 0; roomIndex < LocationsLength; roomIndex++)
    {
        worldMap[roomLocations[roomIndex]] = importantRooms[roomIndex];
    }
};

void World::UpdateRoomsData(){
    std::cout << "Updating Locations With Neighbouring Data" << std::endl;
    std::mt19937 gen(time(0));
    for (int row = 0; row< worldHeight; row++){
        for (int col = 0; col< worldWidth; col++){
            int index = row*worldWidth+col;
            worldMap[index].indexValue = index;

            //std::random_device rd;
            std::uniform_int_distribution<> distr(0, 100);
            if (distr(gen) > ChanceTileIsFree && worldMap[index].Name == Adventure::LocationNameFromEnum(EmptyRoom))
            {
                worldMap[index].usable=false;
                worldMap[index].Name = Adventure::LocationNameFromEnum(Blocked);
                worldMap[index].mapIcon = pathDirections[11];
            }
            else if (worldMap[index].Name == Adventure::LocationNameFromEnum(EmptyRoom))
            {
                worldMap[index].Name = Adventure::LocationNameFromEnum(Grassland);
            }

            if (index > worldWidth-1)
                {worldMap[index].Up =  &worldMap[index-worldWidth];}
            else
                {worldMap[index].Up = NULL;}

            if (index < (worldWidth*worldHeight)-worldWidth)
                {worldMap[index].Down =  &worldMap[index+worldWidth];}
            else
                {worldMap[index].Down = NULL;}

            if (index!=0 &&   index%worldWidth>0 )
                {worldMap[index].Left =  &worldMap[index-1];}
            else
                {worldMap[index].Left =  NULL;}
                
            if (index!= worldWidth*worldHeight && index%worldWidth!=worldWidth-1 )
                {worldMap[index].Right =  &worldMap[index+1];}
            else
                {worldMap[index].Right =  NULL;}
            
            //std::cout <<"~";
        }
        //std::cout<<std::endl;
    }
}

void World::CreatePaths(){
    for (int row = 0; row< worldHeight; row++){
        for (int col = 0; col< worldWidth; col++){
            int index = row*worldWidth+col;
            if (worldMap[index].Name == Adventure::LocationNameFromEnum(Grassland))
            {
                bool up= false;
                bool down= false;
                bool left= false;
                bool right= false;

                if (worldMap[index].Up!= NULL){
                    up=worldMap[index].Up->usable;
                }
                if (worldMap[index].Down!= NULL){
                    down=worldMap[index].Down->usable;
                }
                if (worldMap[index].Left!= NULL){
                    left=worldMap[index].Left->usable;
                }
                if (worldMap[index].Right!= NULL){
                    right=worldMap[index].Right->usable;
                }

                int outcome = 4;
                if (left&&!right) {outcome++;}
                else if (!left&&right) {outcome--;}
                
                if (up&&!down) {outcome+=3;}
                else if (!up&&down) {outcome-=3;}

                if(up&&down&&!left&&!right){
                    outcome=9;
                    worldMap[index].Name = "very narrow bridge.";
                    worldMap[index].Description = "Dont look down!";
                }
                if(!up&&!down&&left&&right){
                    outcome=10;
                    worldMap[index].Name = "very narrow bridge.";
                    worldMap[index].Description = "Dont look down!";
                }

                
                //if(!up&&!down&&!left&&!right){outcome=11;}

                if (((int)up +(int)down+(int)left+(int)right) == (int)1){
                    outcome=12;
                    worldMap[index].Name = "Campfire";
                    worldMap[index].Description = "Stood in a nice corner of the world by the fire is kind of refreshing.";
                }
                else if (((int)up +(int)down+(int)left+(int)right) == (int)0){
                    outcome=11;
                }


                worldMap[index].mapIcon = pathDirections[outcome];
            }
        } 
    }
}


void World::ExpandWorldMap(directions direction){
     switch (direction){
        case directions::Up:{
            worldHeight++;
            Room* map2 = new Room[worldHeight*worldWidth];
            int mapIndex = 0;
            // Set the first row of map tiles to random tile data            
            for (int index = 0; index< worldWidth; index++){
                CreateNewRoom(map2[index]);
                mapIndex = index+1;
            }
            // Add the pre existing map tiles to the array  
            for (int index = 0; index< worldWidth*(worldHeight-1); index++){
                map2[mapIndex] = worldMap[index];
                mapIndex++;
            }
            worldMap=map2;
            break;
        }
        case directions::Down:{
            worldHeight++;
            Room* map2 = new Room[worldHeight*worldWidth];
            int mapIndex = 0;
            for (int index = 0; index< worldWidth*(worldHeight-1); index++){
                map2[index] = worldMap[index];
                mapIndex = index+1;
            }
            // Set the last (new) map tiles to random tile data
            for (int index = mapIndex; index< worldWidth*worldHeight; index++){
                CreateNewRoom(map2[index]);
            }
            worldMap=map2;
            break;
        }
        case directions::Left:{
            worldWidth++;
            Room* map2 = new Room[worldHeight*worldWidth];
            int mapIndex = 0;
            for (int index = 0; index< (worldWidth-1)*worldHeight; index++){
                int row = index/(worldWidth-1);
                int offset = row + 1;
                map2[index+offset] = worldMap[index];
                mapIndex = index+1;
            }
            for (int index = 0; index< worldHeight; index++){
                CreateNewRoom(map2[index*worldWidth]);
            }
            worldMap=map2;
            break;
        }
        case directions::Right:{
            worldWidth++;
            Room* map2 = new Room[worldHeight*worldWidth];
            int mapIndex = 0;
            for (int index = 0; index< (worldWidth-1)*worldHeight; index++){
                int row = index/(worldWidth-1);
                map2[index+row] = worldMap[index];
                mapIndex = index+1;
            }
            for (int index = 0; index< worldHeight; index++){
                CreateNewRoom(map2[((index+1)*worldWidth)-1]);
            }
            worldMap=map2;

            break;
        }
        default:{
        }
    }
    UpdateRoomsData();
};

void World::PlacePlayerInRoom(int x, int y){
    int currentRoomIndex = playerPos[1]*worldWidth+playerPos[0];
    playerPos[0]=x;
    playerPos[1]=y;

    worldMap[currentRoomIndex].playerIsHere = false;
    currentRoomIndex = y*worldWidth+x;
    worldMap[currentRoomIndex].playerIsHere = true;
    playerIndex = currentRoomIndex;
};


void World::NameOfRoomAt(int x, int y)
{
    std::cout << worldMap[ y*worldWidth+x].Name;
};

void World::DescriptionOfRoomAt(int x, int y)
{
    std::cout << worldMap[ y*worldWidth+x].Description;
};

void World::WhereAmI(int x, int y)
{
    std::cout << worldMap[ y*worldWidth+x].Name << std::endl
              << worldMap[ y*worldWidth+x].Description << std::endl;
};