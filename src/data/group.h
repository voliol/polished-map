#ifndef GROUP_H
#define GROUP_H

#include <string>
#include "roof_type.h"
#include "roof_colors.h"
#include "outdoor-sprite-set.h"

class Group {
public:


private:

    std::string* _name;
    Roof_Type _rooftype;
    Roof_Colors* _roofcolors_gbc;
    Roof_Colors* _roofcolors_sgb;
    Outdoor_Sprite_Set* _outsprset;

};

#endif