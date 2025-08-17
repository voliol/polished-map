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

bool Map_Tree::hasGroups() {
	return _poke_project->game() == Poke_Project::game_crystal;
}

bool Map_Tree::populate(Poke_Project *poke_project) {

	// This can cause a segfault, if the program may tries to 
	// populate (including clearing all items) while in the midst 
	// of handling a mapItem...
	// Thus, better handling of maps is needed 
	// (this class should probably not call Main_Window::open_map(char*))
	// TODO

	_poke_project = poke_project;

	clear();

	Fl_Tree_Item *item;
	for (Group* g : poke_project->groups()) {

		if (hasGroups()) {
			item = add((g->name()).c_str());
			usericon(&GROUP_ICON);
		}

		for (Map_Data* m : g->maps()) {
			std::string mapname = m->name();
			if (hasGroups()) {
				mapname = g->name() + "/" + mapname;
			}

			item = add(mapname.c_str());
			item->usericon(&MAP_ICON);
		}
	}
	
	return true;
}

int Map_Tree::handle(int e) {
	switch (e) {
		case FL_PUSH:
			Fl_Tree_Item *item = (Fl_Tree_Item*)find_clicked();
			if ( item ) {
				select(item);
				if ( hasGroups() && item->depth() == 1 ) { 
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
				Config::map_blocks_path(blocks_path, _poke_project->directory().c_str());
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
					filename = _poke_project->directory() + filename;
					_mainWindow->open_map(filename.c_str());
				}
			}
			break;
	}
	// + some way of changing a map's name, and moving it to another group.
	//   By dragging? Though dragging only is a pain.
	//   It might only make sense to change a map's settings while it is open?

}
