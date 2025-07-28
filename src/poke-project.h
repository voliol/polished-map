#ifndef POKE_PROJECT_H
#define POKE_PROJECT_H

#include <string>

/*
 * Represents a pokered/pokecrystal project.
 */

class Poke_Project {
public:
    Poke_Project(const std::string &directory) : _directory(directory) {};

    inline const std::string &directory() { return _directory; }

private:
    const std::string _directory;
};


#endif