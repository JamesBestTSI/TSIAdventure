#ifndef WORLD_H
#define WORLD_H
#include <string>
#include <time.h>
#include "../../Adventure.h"

class World {
    public:
    // The basic structure of a Room a player can visit
    struct Room
    {
        std::string Name = Adventure::LocationNameFromEnum(EmptyRoom); // The rooms name
        std::string Description = "There is nothing here"; // The rooms description
        int mapIcon = 219;
        bool playerIsHere = false;

        int indexValue = 0;
        bool usable = true;
        Room *Up;
        Room *Down;
        Room *Left;
        Room *Right;

        int Inspect = 0;
    };
    const int ChanceTileIsFree = 80;
    const int HIDDENBLOCK = 219;
    const int UD = 186;
    const int LR = 205;
    const int pathDirections[13] = {  176,176,176,
                                                            176,177,176,
                                                            176,176,176,
                                                            186,205, 178, 35};
                                                            // {  201, 203, 187,
                                                            //204, 206, 185,
                                                            //200, 202, 188,
                                                            //186, 205, 177}; //206

    enum directions{Up, Down, Left, Right};
    int worldHeight=150;
    int worldWidth=40;
    int playerPos[2];
    int playerIndex=0;
    Room *worldMap;

    Room *importantRooms;
    int importantRoomsCount=0;


    World();
    ~World();

    void SetWorldSize(int x, int y);
    void CreateWorldMap();
    void CreateImportantRooms();
    void ScatterImportantRooms();
    void DisplayWorldMap();
    void ExpandWorldMap(directions direction);
    void CreateNewRoom(Room &room);
    void CreateNewRoom(Room &room, std::string name,int icn, std::string description);
    void UpdateRoomsData();
    void CreatePaths();
    void PlacePlayerInRoom(int x, int y);
    void NameOfRoomAt(int x, int y);
    void DescriptionOfRoomAt(int x, int y);
    void WhereAmI(int x, int y);

};
#endif