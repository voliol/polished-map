#ifndef MAP_DATA_H
#define MAP_DATA_H

#include <string>
#include "blocks.h"
#include "../tileset.h"
#include "landmark.h"
#include "connections.h"
#include "encounter-group.h"
#include "fishing-group.h"
#include "headbutt-group.h"

class Group;

using Music = std::string;

class Map_Data {

    // TODO
    // I want this class to be named "Map", but there is already a "Map" class.
    // Still, it feels easier to rewrite it from scratch; 
    // "Map_Data" is a temporary name until that is done.
public:

    enum Environment {
        TOWN, ROUTE, INDOOR, ENVIRONMENT_5, GATE, DUNGEON
    };

    // "Time of Day" Palette
    enum ToD_Palette {
        PALETTE_AUTO, PALETTE_MORN, PALETTE_DAY, PALETTE_NITE, PALETTE_DARK
    };

    Map_Data(std::string name) : _name(name) {};

    std::string& name() {return _name;}

private:

    std::string _name;

    Group* _group;
    Blocks* _blocks;
    Tileset* _tileset;

    Environment _environment;
    Landmark* _landmark;
    Music _music;
    bool _hasPhoneService;
    ToD_Palette _tod_palette;
    Block_Tile _border_block;

    Connections _connections;

    Encounter_Group* _encounter_group;
    Fishing_Group* _fishing_group;
    Headbutt_Group* _headbutt_group;

};

#endif