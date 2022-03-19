#ifndef WORLD_H
#define WORLD_H
#include <string>

class World {
    
    // The basic structure of a Room a player can visit
    struct Room{
        std::string Name = "Empty Room";                                    // The rooms name
        std::string Description = "There is nothing here";          // The rooms description
        int mapIcon = '#';
    };


    public:
    enum directions{Up, Down, Left, Right};
    int worldHeight=10;
    int worldWidth=10;
    Room *worldMap;



    World();
    ~World();

    void CreateWorldMap();
    void DisplayWorldMap();
    void ExpandWorldMap(directions direction);
    void CreateNewRoom(Room &room);

};
#endif