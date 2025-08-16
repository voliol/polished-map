#ifndef GROUP_H
#define GROUP_H

#include <string>
#include <vector>
#include "roof_type.h"
#include "roof_colors.h"
#include "outdoor-sprite-set.h"
#include "map-data.h"

class Group {
public:

    Group(std::string name) : _name(name) {} 
    // TODO: init the other members

    std::string& name() {return _name;}
    void add_map(Map_Data* map);
    const std::vector<Map_Data*>& maps() {return _maps;}

private:

    std::string _name;
    Roof_Type _rooftype;
    Roof_Colors* _roofcolors_gbc;
    Roof_Colors* _roofcolors_sgb;
    Outdoor_Sprite_Set* _outsprset;

    std::vector<Map_Data*> _maps;
};

#endif