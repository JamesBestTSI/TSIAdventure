#ifndef MAPDESIGNER_H
#define MAPDESIGNER_H
#include <string>

const int HEIGHTOFWORLD = 10;
const int LENGTHOFWORLD = 20;

class MapDesigner{

    public:
        const int HIDDENBLOCK = 219;
        const int UD = 186;
        const int LR = 205;
        const int directions[9] = {201, 203, 181,
                                   204, 206, 185,
                                   200, 202, 188};

        // The basic structure of a Room a player can visit
        struct Room
        {
            std::string Name = "Blank";        // The rooms name
            std::string Description = "Blank"; // The rooms description
            int mapIcon = 219;
    };

    // The basic structure of the world map
    struct Map {
        Room rooms[LENGTHOFWORLD][HEIGHTOFWORLD];
    };

    Map worldMap;
    int rows;
    int cols;
    MapDesigner();
    ~MapDesigner();
    void CreateWorldMap();
    void CreateRoom(std::string name, int icon, Room &room);
    void DrawWorldMap();
    void NameOfRoomAt(int x, int y);
    void DescriptionOfRoomAt(int x, int y);
    void WhereAmI(int x, int y);

};
#endif