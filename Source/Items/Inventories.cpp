#include "inventories.h"
#include <string>


Inventories::Inventories(){};
Inventories::~Inventories(){};

void Inventories::GiveItem(ItemNames item){
    Item additionalItem;
    if (item == ItemNames::Ladder)
    {
        additionalItem.Name = "Ladder";
        additionalItem.Description = "Can be used to reach high places.";
        additionalItem.amount = 1;
    }
    if (item == ItemNames::Rabbit)
    {
        additionalItem.Name = "Rabbit";
        additionalItem.Description = "Looks like some good meat.";
        additionalItem.amount = 1;
    }

    bool itemExists = false;
    for (int index = 0; index < 10; index++){
        if (itemList.items[index].Name == additionalItem.Name)
        {
            itemList.items[index].amount++;
            itemExists + true;
        }
    }
    if (itemExists == false){
        for (int index = 0; index < 10; index++)
        {
            if (itemList.items[index].Name == "Empty")
            {
                itemList.items[index] = additionalItem;
                return;
            }
        }
    }
};


void Inventories::ClearItem(int index){
    itemList.items[index] = Item();
}