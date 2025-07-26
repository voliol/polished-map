#ifndef MAP_TREE_H
#define MAP_TREE_H

#include "widgets.h"

class Map_Tree : public OS_Tree {
public:
	Map_Tree(int x, int y, int w, int h, const char *l = NULL);
    
    bool populate(const char *directory);
};

#endif