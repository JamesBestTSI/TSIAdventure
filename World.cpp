#include "World.h"
#include <iostream>


World::World(){};
World::~World(){};

void World::CreateWorldMap(){
    worldMap = new Room[worldHeight*worldWidth];
};

void World::CreateNewRoom(Room &room){
    room.mapIcon='@';
};

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
            for (int index = mapIndex; index< worldWidth*worldHeight; index++){
                map2[index] = worldMap[index];
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
};



void World::DisplayWorldMap(){
    for (int row = 0; row< worldHeight; row++){
        for (int col = 0; col< worldWidth; col++){
            std::cout << (char)worldMap[row*worldWidth+col].mapIcon;
        }
        std::cout << std::endl;
    }
};

