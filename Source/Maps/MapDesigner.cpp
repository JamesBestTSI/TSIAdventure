#include <iostream>
#include <string>
#include <random>
#include "MapDesigner.h"

// LENGTHOFWORLD
// HEIGHTOFWORLD

MapDesigner::MapDesigner(){};
MapDesigner::~MapDesigner(){};


void MapDesigner::CreateRoom(std::string name, int icon, Room &room){
    room.Name = name;
    room.mapIcon = icon;
};

void MapDesigner::CreateWorldMap(){

    const int roomcount = 9;
    int usedRooms[roomcount+1][2];

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distr(0, HEIGHTOFWORLD - 1);
    std::uniform_int_distribution<> distr2(0, LENGTHOFWORLD - 1);
    for (int n = 0; n < roomcount; ++n)
    {
        usedRooms[n][1] = distr2(gen);
        usedRooms[n][0] = distr(gen);
        for (int m = 0; m < n;m++)
        {
            if (usedRooms[m][1] == usedRooms[n][1] && usedRooms[m][0] == usedRooms[n][0]){
                n--;
            }
        }
    }

    // ADD DESCRIPTIONS!!!!!!!!!!
    CreateRoom("Small House", 127, worldMap.rooms[usedRooms[0][1]][usedRooms[0][0]]);
    CreateRoom("Grassland", 177, worldMap.rooms[usedRooms[1][1]][usedRooms[1][0]]);
    CreateRoom("Wood Cabin", 35, worldMap.rooms[usedRooms[2][1]][usedRooms[2][0]]);
    CreateRoom("Large Tree", 20, worldMap.rooms[usedRooms[3][1]][usedRooms[3][0]]);
    CreateRoom("Shop", 36, worldMap.rooms[usedRooms[4][1]][usedRooms[4][0]]);
    CreateRoom("Graveyard", 241, worldMap.rooms[usedRooms[5][1]][usedRooms[5][0]]);
    CreateRoom("Lake", 229, worldMap.rooms[usedRooms[6][1]][usedRooms[6][0]]);
    CreateRoom("Cave", 182, worldMap.rooms[usedRooms[7][1]][usedRooms[7][0]]);
    CreateRoom("Castle", 222, worldMap.rooms[usedRooms[8][1]][usedRooms[8][0]]);

    rows = sizeof worldMap.rooms / sizeof worldMap.rooms[0];
    cols = sizeof worldMap.rooms[0] / sizeof(Room);
};

void MapDesigner::DrawWorldMap(){
    // Loop through each array row and col to draw out the map
    for (int col = 0; col < cols;col++){
        for (int row = 0; row < rows; row++)
        {
            std::cout << (char)worldMap.rooms[row][col].mapIcon;
        }
        std::cout << std::endl;
    }
};

void MapDesigner::NameOfRoomAt(int x, int y)
{
    std::cout << worldMap.rooms[y][x].Name;
};

void MapDesigner::DescriptionOfRoomAt(int x, int y)
{
    std::cout << worldMap.rooms[y][x].Description;
};

void MapDesigner::WhereAmI(int x, int y)
{
    std::cout << worldMap.rooms[y][x].Name << std::endl
              << worldMap.rooms[y][x].Description << std::endl;
};