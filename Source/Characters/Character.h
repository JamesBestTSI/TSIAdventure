#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include "../Items/Inventories.cpp"

class Character{
   

    public:
     struct CharacterStats {
        std::string Name = "Blank";
        int HPMax = 0;
        int MPMax = 0;
        int HPCurrent = 0;
        int MPCurrent = 0;
        int Str = 0;
        int Int = 0;
        Inventories inventory;
    };
        CharacterStats characterData;
        Character();
        Character(std::string name);
        
        Character(std::string name, int hpmax, int mpmax, int str, int intel);
        ~Character();
        void DisplayCharacterStats() ;
        void DisplayCharacterInventory() ;
        void SetName(std::string name);

};
#endif