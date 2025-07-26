#ifndef MAP_TREE_H
#define MAP_TREE_H

#pragma warning(push, 0)
#include <FL/Fl_Tree_Item.H>
#pragma warning(pop)

#include "widgets.h"

class Map_Tree : public OS_Tree {
public:
	Map_Tree(int x, int y, int w, int h, const char *l = NULL);

    bool populate(const char *directory);
    int handle(int e);

private:
    void handleGroupItem(Fl_Tree_Item *item);
    void handleMapItem(Fl_Tree_Item *item);
};

#endif