#ifndef INVENTORIES_H
#define INVENTORIES_H
#include <string>


class Inventories{
   

    public:
        struct Item {
            std::string Name = "Empty";
            std::string Description = "Empty";
        };

        struct Inventory {
            Item items[10];
        };
 
        Inventory itemList;
        Inventories();
        ~Inventories();


};
#endif