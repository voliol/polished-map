#include "poke-project.h"

#include <fstream>
#include <iostream>

#include "utils.h" // for DIR_SEP

Poke_Project::Poke_Project(const std::string &directory) : 
        _directory{directory}, 
        _game{determine_game(directory)}
    {
        std::cout << "Initializing Poke_Project" << '\n'
            << "dir:" << directory << '\n'
            << "gametype:" << game() << std::endl;
        init_groups();
        init_landmarks();
        init_outdoor_sprite_sets();
        init_fishing_groups();
        init_headbutt_groups();
    };

const Poke_Project::Game Poke_Project::determine_game(const std::string &directory) {
    // Is home.asm >= 200 lines?
    //   yes -> pokered
    //   no  -> pokecrystal

    std::ifstream ifs {directory + DIR_SEP + "home.asm"};

    int count = 0;
    std::string line;
    while (std::getline(ifs, line)) {
        ++count;
    }

    return count >= 200 ? Poke_Project::game_red : Poke_Project::game_crystal;
}

void Poke_Project::init_groups() {
    if (_game == game_red) {

        Group* g = new Group {"FAKE_GROUP"};
        _groups.push_back(g);
        // TODO: get the map data

    } else { // game_crystal

        std::ifstream ifs {_directory + DIR_SEP + "constants" + DIR_SEP + "map_constants.asm"};

        std::string line;
        Group* g;
        while(std::getline(ifs, line)) {
		    std::istringstream lss(line);

            std::string macro;
            if (!leading_macro(lss, macro)) { continue; }
            
            if (macro == "newgroup") {
                std::string groupname;
                lss >> groupname;
                g = new Group{groupname};
                _groups.push_back(g);
                std::cout << "Adding group: " << groupname << std::endl;
            
            } else if (macro == "map_const"    // "map_const": pokecrystal
					|| macro == "mapgroup" // "mapgroup": pokecrystal pre-2018
					) {
                if (g) {
                    std::string mapname;
                    lss >> mapname;
                    mapname.pop_back(); // remove comma
                    Map_Data* m = new Map_Data{mapname};
                    g->add_map(m);

                    std::cout << "\tAdding map: " << mapname << std::endl;
                }
		    }
        }

    }
}

void Poke_Project::init_landmarks() {
    // TODO
}

void Poke_Project::init_outdoor_sprite_sets() {
    // TODO
}

void Poke_Project::init_fishing_groups() {
    // TODO
}

void Poke_Project::init_headbutt_groups() {
    // TODO
}

std::ostream& operator<<(std::ostream& out, const Poke_Project& proj) {
    out << "[";
    switch (proj._game) {
        case Poke_Project::game_red:
            out << "pokered";
            break;
        case Poke_Project::game_crystal:
            out << "pokecrystal";
            break;
    }

    out << " project at " << proj._directory;
    out << "]";

    return out;
}