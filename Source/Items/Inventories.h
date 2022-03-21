#ifndef INVENTORIES_H
#define INVENTORIES_H
#include <string>


class Inventories{  

    public:
        struct Item {
            std::string Name = "Empty";
            std::string Description = "Empty";
            int amount = 0;
        };

        struct Inventory {
            Item items[10];
        };
 
        Inventory itemList;
        Inventories();
        ~Inventories();
        void GiveItem(ItemNames item);
        void ClearItem(int index);
};
#endif