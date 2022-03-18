#include <iostream>
#include <iterator>
#include "Character.h" 
#include "../Items/Inventories.h"


Character::Character(){}

Character::Character(std::string name){
    characterData.Name = name;   
}

Character::Character(std::string name, int hpmax, int mpmax, int str, int intel){
    
    characterData.Name = name;   
    characterData.HPMax = hpmax;
    characterData.MPMax = mpmax; 
    characterData.HPCurrent = hpmax;
    characterData.MPCurrent = mpmax;
    characterData.Int = intel;
    characterData.Str = str;
}

Character::~Character(){}


void Character::DisplayCharacterStats() {
    std::cout << "        ,,,\n       (o o)\n----oOO--()--OOo----" << std::endl;
    std::cout << "Name: " << characterData.Name << std::endl;
    std::cout << "HP: " << characterData.HPCurrent << "/" << characterData.HPMax << std::endl;
    std::cout << "HP: " << characterData.MPCurrent << "/" << characterData.MPMax << std::endl;
    std::cout << "Int: " << characterData.Int << std::endl;
    std::cout << "Str: " << characterData.Str << std::endl;
    //DisplayCharacterInventory(character);
}

void Character::DisplayCharacterInventory() {
    int slotNumber = 0;
    std::cout << "\n----Inventory----" << std::endl;
    for(int Index=0; Index<sizeof(characterData.inventory.itemList.items); Index++) {
                std::cout << "Slot " << Index << " - " << characterData.inventory.itemList.items[Index].Name  << "\n  -" << characterData.inventory.itemList.items[Index].Description << std::endl;
    }
    //for (auto &item : characterData.inventory.itemList) {
    //    std::cout << "Slot " << slotNumber << " - " << item.Name << "\n  -" << item.Description << std::endl;
    //}
}

void Character::SetName(std::string name){
        characterData.Name = name;
}