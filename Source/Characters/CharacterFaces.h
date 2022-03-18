#ifndef CHARACTERFACES_H
#define CHARACTERFACES_H 
#include <string>

class CharacterFaces{

public:
    struct Eyes
    {
        std::string Selection[8] = {
            "|    0 / 0    | ",
            "|    o / o    | ",
            "|    - / -    | ",
            "|    U / U    | ",
            "|    ^ / ^    | ",
            "|    | / |    | ",
            "|    + / +    | ",
            "|    - / O    | "};
    };

    struct Mouth
    {
        std::string Selection[7] = {
            "   \\  -_-  /",
            "   \\  ---  /",
            "   \\  _-_  /",
            "   \\  -x-  /",
            "   \\  www  /",
            "   \\  vvv  /",
            "   \\  |_|  /"};
    };

    Eyes AvailableEyes;
    Mouth AvailableMouths;
    CharacterFaces();
    ~CharacterFaces();
};
#endif