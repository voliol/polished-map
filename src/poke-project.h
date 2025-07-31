#ifndef POKE_PROJECT_H
#define POKE_PROJECT_H

#include <string>
#include <iostream>

/*
 * Represents a pokered/pokecrystal project.
 */
class Poke_Project {
public:
    enum Game {
        game_red, game_crystal
    };

    Poke_Project(const std::string &directory) : 
        _directory(directory), 
        _game(determine_game(directory)) 
        {};

    inline const std::string &directory() const { return _directory; }
    inline const Game game() const { return _game; }

private:
    const Game determine_game(const std::string &directory);

    const std::string _directory;
    const Game _game;

    friend std::ostream& operator<<(std::ostream& out, const Poke_Project& proj);
};

#endif