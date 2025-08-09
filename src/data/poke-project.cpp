#include "poke-project.h"

const Poke_Project::Game Poke_Project::determine_game(const std::string &directory) {
    
    // TODO
    return Poke_Project::game_crystal;
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