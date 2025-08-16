#ifndef POKE_PROJECT_H
#define POKE_PROJECT_H

#include <string>
#include <iostream>
#include <vector>

#include "group.h"
#include "landmark.h"
#include "fishing-group.h"
#include "headbutt-group.h"

/**
 * Represents a pokered/pokecrystal project.
 * Maps are accessed through "Groups", even in pokered projects 
 * that don't have Groups per-se.
 */
class Poke_Project {
public:
    enum Game {
        game_red, game_crystal
    };

    Poke_Project(const std::string &directory);

    const std::string& directory() const { return _directory; }
    const Game game() const { return _game; }
    const std::vector<Group*>& groups() {return _groups;}

private:
    const Game determine_game(const std::string &directory);
    void init_groups();
    void init_landmarks();
    void init_outdoor_sprite_sets();
    void init_fishing_groups();
    void init_headbutt_groups();

    const std::string _directory;
    const Game _game;

    std::vector<Group*> _groups;
    std::vector<Landmark*> _landmarks;
    std::vector<Outdoor_Sprite_Set*> _outdoorSpriteSets;
    // TODO: maybe should have a tileset vector here too?
    std::vector<Fishing_Group*> _fishingGroups;
    std::vector<Headbutt_Group*> _headbuttGroups;

    friend std::ostream& operator<<(std::ostream& out, const Poke_Project& proj);
};

#endif