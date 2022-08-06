// Copyright (C) 2022 Ryan Pullinger and Natalie Wiggins
//
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with this program. If not, see <https://www.gnu.org/licenses/>.

#ifndef GELCUBE_SRC_TUI_HH_
#define GELCUBE_SRC_TUI_HH_

#include <vector>

#include <ncurses.h>

#include <string>

namespace gelcube
{
class Panel;
	
// Manages the Terminal User Interface.
class Tui
{
public:
    // Initializes ncurses and starts the main UI loop. Returns an exit code for
    // the program.
    static int start();

private:
    static std::vector<Panel> panels;
};

class Panel
{
	// Panel class to store more imformation around windows
public:
	std::string name;
    Panel(int h, int w, int y, int x, std::string n);
	void draw();
    WINDOW *getwin();
    int getX();
    int getY();
	int getHeight();
	int getWidth();
	void resize(int h, int w);
	void movewin(int y, int x);
	
private:
    int height, width, startY, startX;
    WINDOW *win;
};
  
}; // namespace gelcube

#endif // GELCUBE_SRC_TUI_HH_
