#ifndef MAP_TREE_H
#define MAP_TREE_H

#pragma warning(push, 0)
#include <FL/Fl_Tree_Item.H>
#pragma warning(pop)

#include "widgets.h"
#include "main-window.h"
#include "poke-project.h"

// TODO: just declaring the class here *can't* be the right way of doing it, right?
class Main_Window; 

class Map_Tree : public OS_Tree {
public:
	Map_Tree(int x, int y, int w, int h, Main_Window *mainWindow);

    bool populate(Poke_Project *poke_project);
    int handle(int e);

private:
    void handleGroupItem(Fl_Tree_Item *item);
    void handleMapItem(Fl_Tree_Item *item);

    Main_Window *_mainWindow; // lazy way to get access to open_map() for now
    Poke_Project *_poke_project;
    bool populated;
};

#endif