#ifndef MAPDESIGNER_H
#define MAPDESIGNER_H
#include <string>

class MapDesigner{

    public:
        struct Room {
        std::string Name;
    };


    struct Map {
        Room rooms[3][3];
    };


    Map worldMap;
    MapDesigner();
    ~MapDesigner();

    void CreateWorldMap();

    Room CreateRoom(std::string name);


};
#endif