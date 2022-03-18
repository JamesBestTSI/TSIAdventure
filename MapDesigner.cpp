#include <string>
#include "MapDesigner.h"



MapDesigner::MapDesigner(){};
MapDesigner::~MapDesigner(){};


MapDesigner::Room MapDesigner::CreateRoom(std::string name){
    Room tempRoom;
    tempRoom.Name = name;
    return tempRoom;
};

void MapDesigner::CreateWorldMap(){
    worldMap.rooms[0][0] = CreateRoom("Small House");
    worldMap.rooms[0][1] = CreateRoom("Grassland");
    worldMap.rooms[0][2] = CreateRoom("Wood Cabin");
    worldMap.rooms[1][0] = CreateRoom("Large Tree");
    worldMap.rooms[1][1] = CreateRoom("Shop");
    worldMap.rooms[1][2] = CreateRoom("Graveyard");
    worldMap.rooms[2][0] = CreateRoom("Lake");
    worldMap.rooms[2][1] = CreateRoom("Cave");
    worldMap.rooms[2][2] = CreateRoom("Castle");
};