#include <fstream>
#include <regex>
#include <iostream>

#include "map-tree.h"
#include "config.h"
#include "utils.h"
#include "main-window.h"
#include "icons.h"

Map_Tree::Map_Tree(int x, int y, int w, int h, Main_Window *mainWindow) 
	: OS_Tree(x, y, w, h), _mainWindow(mainWindow) {
	showroot(false);
	widgetmarginleft(0);
	connectorstyle(Fl_Tree_Connector::FL_TREE_CONNECTOR_NONE);
    // empty
}

bool Map_Tree::populate(const char *directory) {

	// We only allow populating once, since as things are, 
	// the program may try to populate (including clearing all items)
	// while in the midst of handling a mapItem...
	// Which causes a segfault.
	// This is not ideal of course, since the user *could* be trying
	// to open up a map from a new project, and then the tree *should*
	// be repopulated.
	// When projects are handled better, this can be changed.
	if (populated) return true;

	clear();
	
	char map_constants[FL_PATH_MAX] = {};
	Config::map_constants_path(map_constants, directory);

	std::ifstream ifs;
	open_ifstream(ifs, map_constants);

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
			usericon(&GROUP_ICON);

		} else if (macro == "map_const"    // "map_const": pokecrystal
					|| macro == "mapgroup" // "mapgroup": pokecrystal pre-2018
					|| macro == "mapconst" // "mapconst": pokered
					) {
			lss >> mapname;
			mapname.pop_back(); // remove comma
			item = add((groupname + "/" + mapname).c_str());
			item->usericon(&MAP_ICON);
		}
	}

	populated = true;
	return true;
}

int Map_Tree::handle(int e) {
	switch (e) {
		case FL_PUSH:
			Fl_Tree_Item *item = (Fl_Tree_Item*)find_clicked();
			if ( item ) {
				select(item);
				if ( item->depth() == 1 ) { 
					handleGroupItem(item);
				} else { 
					handleMapItem(item);
				}
			}
		break;
	}
	return(Fl_Tree::handle(e));
}

void Map_Tree::handleGroupItem(Fl_Tree_Item *item) {
	switch (Fl::event_button()) {
		case FL_LEFT_MOUSE:
			// Left double click -> group settings
			if (Fl::event_clicks() == 1) {
				item->label("left double click");
			}
			break;
		case FL_RIGHT_MOUSE:
			// Right click -> option dropdown:
			// - add new map
			// - group settings
			// - delete group
			//		- big confirmation if clicked
			item->label("right click");
			break;
	}
}

void Map_Tree::handleMapItem(Fl_Tree_Item *item) {
	switch (Fl::event_button()) {
		case FL_LEFT_MOUSE:
			// Double left click -> open map
			if (Fl::event_clicks() == 1) { // double click

				std::string id = item->label();
				macro_to_titlecase(id);
				// _Blocks for modern pokecrystal+red, 
				// _Blockdata for old pokecrystal, 
				// Blocks for old pokered
				id.append("(_Blocks|_Blockdata|Blocks):");
				std::regex idReg(id);

				char blocks_path[FL_PATH_MAX] = {};
				Config::map_blocks_path(blocks_path, _mainWindow->directory().c_str());
				std::ifstream ifs;
				open_ifstream(ifs, blocks_path);

				std::string filename;
				bool foundID = false;
				while (ifs.good()) {

					std::string line;
					std::getline(ifs, line);

					if (std::regex_search(line, idReg)) {
						foundID = true;
					}

					if (foundID) {
						std::regex r("INCBIN \"([^\"]*)");
    					std::smatch m;
    					std::regex_search(line, m, r);

						if (m.length() != 0) {
							filename = m.str(1);
							break;
						}
					}
				}
				
				if (!filename.empty()) {
					filename = std::string {_mainWindow->directory()} + filename;
					_mainWindow->open_map(filename.c_str());
				}

				item->label("left foobar click");
			}
			break;
	}
	// + some way of changing a map's name, and moving it to another group.
	//   By dragging? Though dragging only is a pain.
	//   It might only make sense to change a map's settings while it is open?

}
