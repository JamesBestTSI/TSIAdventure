#ifndef ADVENTURE_H
#define ADVENTURE_H
#include <string>

enum LocationName
{
    Blocked,
    EmptyRoom,
    SmallHouse,
    Swamp,
    WoodCabin,
    LargeTree,
    Graveyard,
    Lake,
    Cave,
    Castle,
    Grassland,
    Shop,
    Campfire
};

enum ItemNames
{
    Ladder,
    Rabbit
};

const int LocationsLength = 12;

class Adventure{
    public:
        static std::string LocationNameFromEnum(enum LocationName value)
        {
            switch (value)
            {
            case 0:
                return "BLOCKED";
            case 1:
                return "Empty Room";
            case 2:
                return "Small House";
            case 3:
                return "Swamp";
            case 4:
                return "Wood Cabin";
            case 5:
                return "Large Tree";
            case 6:
                return "Graveyard";
            case 7:
                return "Lake";
            case 8:
                return "Cave";
            case 9:
                return "Castle";
            case 10:
                return "Grassland";
            case 11:
                return "Shop";
            case 12:
                return "Campfire";
            }
            return "";
        };

        static std::string LocationDescriptionFromEnum(enum LocationName value)
        {
            switch (value)
            {
            case 0:
                return "BLOCKED";
            case 1:
                return "Empty Room";
            case 2:
                return "Small House";
            case 3:
                return "Swamp";
            case 4:
                return "Wood Cabin";
            case 5:
                return "Large Tree";
            case 6:
                return "Graveyard";
            case 7:
                return "Lake";
            case 8:
                return "Cave";
            case 9:
                return "Castle";
            case 10:
                return "Grassland";
            case 11:
                return "Shop";
            case 12:
                return "Campfire";
            }
            return "";
        };

        static char LocationIconFromEnum(enum LocationName value)
        {
            switch (value)
            {
            case 0:
                return 176;
            case 1:
                return 176;
            case 2:
                return 127;
            case 3:
                return 167;
            case 4:
                return 37;
            case 5:
                return 20;
            case 6:
                return 241;
            case 7:
                return 229;
            case 8:
                return 182;
            case 9:
                return 222;
            case 10:
                return 176;
            case 11:
                return 36;
            case 12:
                return 35;
            }
            return 176;
        };

    static LocationName EnumFromLocationName(std::string const &inString)
    {
        if (inString == LocationNameFromEnum(Blocked))
            return Blocked;
        if (inString == LocationNameFromEnum(EmptyRoom))
            return EmptyRoom;
        if (inString == LocationNameFromEnum(SmallHouse))
            return SmallHouse;
        if (inString == LocationNameFromEnum(Swamp))
            return Swamp;
        if (inString == LocationNameFromEnum(WoodCabin))
            return WoodCabin;
        if (inString == LocationNameFromEnum(LargeTree))
            return LargeTree;
        if (inString == LocationNameFromEnum(Graveyard))
            return Graveyard;
        if (inString == LocationNameFromEnum(Lake))
            return Lake;
        if (inString == LocationNameFromEnum(Cave))
            return Cave;
        if (inString == LocationNameFromEnum(Castle))
            return Castle;
        if (inString == LocationNameFromEnum(Grassland))
            return Grassland;
        if (inString == LocationNameFromEnum(Shop))
            return Shop;
        if (inString == LocationNameFromEnum(Campfire))
            return Campfire;

        return Blocked;
    };
};
#endif