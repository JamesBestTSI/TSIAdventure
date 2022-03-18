#ifndef CHARACTER_H
#define CHARACTER_H
#include <string>
#include "../Items/Inventories.cpp"

class Character{ 
    public:
     struct CharacterStats {
        std::string Name = "Blank";
        int Age = 0;
        bool LeftHanded = false;

        int HPMax = 0;
        int MPMax = 0;
        int HPCurrent = 0;
        int MPCurrent = 0;

        int Hunger = 0;

        int Str = 0;
        int Int = 0;

        Inventories inventory;

        std::string Hair = "      ***\n    *******\n  ***********";
        std::string Face1 = "/\\* ### ### */\\";
        std::string Eyes = "|    @ / @    | ";
        std::string Face3 = "\\/\\    ^    /\\/";
        std::string Mouth = "   \\  ===  /";
        std::string Face5 = "    \\_____/";
        std::string Face6 = "     _|_|_ ";
    };
        CharacterStats characterData;
        Character();
        Character(std::string name);
        
        Character(std::string name, int hpmax, int mpmax, int str, int intel);
        ~Character();

        void DisplayCharacterFace();

        void DisplayCharacterStats();
        void DisplayCharacterInventory();


        void SetName(std::string name);
        void SetAge(int age);
        void SetMainHandLeft(bool leftHanded);
        void EditHungerBy(int change);
        void ChangeEyes();
        void ChangeMouth();
};
#endif