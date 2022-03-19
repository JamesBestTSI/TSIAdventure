#include <iostream>
#include <iterator>
#include "Character.h"
#include "CharacterFaces.h"
#include "../../Source/System/CoreFunctions.h"
#include "../Items/Inventories.h"

Character::Character(){};

Character::Character(std::string name){
    characterData.Name = name;
};

Character::Character(std::string name, int hpmax, int mpmax, int str, int intel){
    
    characterData.Name = name;   
    characterData.HPMax = hpmax;
    characterData.MPMax = mpmax; 
    characterData.HPCurrent = hpmax;
    characterData.MPCurrent = mpmax;
    characterData.Int = intel;
    characterData.Str = str;
};

Character::~Character(){}

void Character::DisplayCharacterFace()
{
    std::cout << characterData.Hair << std::endl;
    std::cout << characterData.Face1 << std::endl;
    std::cout << characterData.Eyes << std::endl;
    std::cout << characterData.Face3 << std::endl;
    std::cout << characterData.Mouth << std::endl;
    std::cout << characterData.Face5 << std::endl;
    std::cout << characterData.Face6 << std::endl;
};

void Character::DisplayCharacterStats()
{
    std::cout << "        ,,,\n       (o o)\n----oOO--()--OOo----" << std::endl;
    std::cout << "Name: " << characterData.Name << std::endl << " --- ";
    std::cout << "HP: " << characterData.HPCurrent << "/" << characterData.HPMax <<  " --- ";
    std::cout << "MP: " << characterData.MPCurrent << "/" << characterData.MPMax << " --- ";
    std::cout << "Hunger: " << characterData.Hunger << " --- ";
    std::cout << "Int: " << characterData.Int << " --- ";
    std::cout << "Str: " << characterData.Str << std::endl;
    // DisplayCharacterInventory(character);
};

void Character::DisplayCharacterInventory()
{
    int slotNumber = 0;
    std::cout << "\n----Inventory----" << std::endl;
    for (int Index = 0; Index < 10; Index++)
    {
        if(characterData.inventory.itemList.items[Index].Name != "Empty" || Index<3){
            std::cout << "Slot " << Index << " - " << characterData.inventory.itemList.items[Index].Name << "\n  -" << characterData.inventory.itemList.items[Index].Description << std::endl;
        }
    }
    // for (auto &item : characterData.inventory.itemList) {
    //     std::cout << "Slot " << slotNumber << " - " << item.Name << "\n  -" << item.Description << std::endl;
    // }
};

void Character::SetName(std::string name)
{
    characterData.Name = name;
};

void Character::SetAge(int age)
{
    characterData.Age = age;
};

void Character::SetMainHandLeft(bool leftHanded)
{
    characterData.LeftHanded = leftHanded;
};

void Character::EditHungerBy(int change)
{
    characterData.Hunger += change;
};

void Character::ChangeEyes()
{
    CoreFunctions core = CoreFunctions();
    CharacterFaces faces = CharacterFaces();
    int eyesIndex = 0;
    bool settingEyes = true;
    while (settingEyes)
    {
        system("CLS");
        characterData.Eyes = faces.AvailableEyes.Selection[eyesIndex];
        DisplayCharacterFace();
        std::cout << "Select Eyes (0-7), any other number to exit: ";
        int option = core.GetInt();
        if (option < 8 && option >= 0)
        {
            eyesIndex = option;
        }
        else
        {
            settingEyes = false;
        }
    }
};

void Character::ChangeMouth()
{
    CoreFunctions core = CoreFunctions();
    CharacterFaces faces = CharacterFaces();
    int mouthIndex = 0;
    bool settingMouth = true;
    while (settingMouth)
    {
        system("CLS");
        characterData.Mouth = faces.AvailableMouths.Selection[mouthIndex];
        DisplayCharacterFace();
        std::cout << "Select Eyes (0-6), any other number to exit: ";
        int option = core.GetInt();
        if (option < 7 && option >= 0)
        {
            mouthIndex = option;
        }
        else
        {
            settingMouth = false;
        }
    }
};
