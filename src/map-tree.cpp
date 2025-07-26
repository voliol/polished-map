#include <fstream>

#include "map-tree.h"
#include "config.h"
#include "utils.h"
#include "icons.h"

Map_Tree::Map_Tree(int x, int y, int w, int h, const char* l) : OS_Tree(x, y, w, h, l) {
	showroot(false);
	widgetmarginleft(0);
	connectorstyle(Fl_Tree_Connector::FL_TREE_CONNECTOR_NONE);
    // empty
}

bool Map_Tree::populate(const char *directory) {
	
	char map_constants[FL_PATH_MAX] = {};
	Config::map_constants_path(map_constants, directory);

	std::ifstream ifs;
	open_ifstream(ifs, map_constants);
	if (!ifs.good()) { 
		return false;
	}


	clear();
	
	std::string groupname, mapname;
	Fl_Tree_Item *item;
	while (ifs.good()) {
		std::string line;
		std::getline(ifs, line);
		std::istringstream lss(line);

		std::string macro;
		if (!leading_macro(lss, macro)) { continue; }

		if (macro == "newgroup") {
			lss >> groupname;
			item = add(groupname.c_str());
			item->usericon(&GROUP_ICON);

		} else if (macro == "map_const"   // "map_const": pokecrystal
					|| macro == "mapgroup" // "mapgroup": pokecrystal pre-2018
					|| macro == "mapconst" // "mapconst": pokered
					) {
			lss >> mapname;
			item = add((groupname + "/" + mapname).c_str());
			item->usericon(&MAP_ICON);
		}
	}

	return true;
}