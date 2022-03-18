#ifndef CHARACTERS_H
#define CHARACTERS_H
#include <string>
#include "Inventories.cpp"

class Characters{
    struct Character {
        std::string Name = "Blank";
        int HPMax = 0;
        int MPMax = 0;
        int HPCurrent = 0;
        int MPCurrent = 0;
        int Str = 0;
        int Int = 0;
        Inventories inventory;
    };

    public:
        Character characterData;
        Characters();
        ~Characters();
        void DisplayCharacterStats() ;
        void DisplayCharacterInventory() ;
        void SetName(std::string name);

};
#endif