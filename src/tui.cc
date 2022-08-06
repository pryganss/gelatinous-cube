// Terminal User Interface.
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

#include "tui.hh"

#include <cstdlib>

#include <string>

#include <ncurses.h>

namespace gelcube
{

std::vector<Panel> Tui::panels;

int Tui::start()
{
    // Screen initialization.
    // TODO(Natalie): Remove forced buffer size; we'll need to update window
    // initialization.
    initscr();
    noecho();
    cbreak();
    resizeterm(31, 98);
    curs_set(0);

    // Window initialization.
    // TODO(Natalie): Implement dynamic assignment of window sizes.
    panels = {
		Panel(31, 36, 0, 0, "1"),
        Panel(5, 25, 0, 36, "2"),
        Panel(3, 25, 5, 36, "3"),
        Panel(23, 25, 8, 36, "4"),
        Panel(31, 36, 0, 61, "5")
    };

    for (auto& panel : panels)
        panel.draw();

    refresh();

	for (auto& panel : panels)
		wrefresh(panel.getwin());
	
    // Main loop.
    while (getch() != static_cast<int>('q')) {};

    // End.
    endwin();

    return EXIT_SUCCESS;
}
	

Panel::Panel(int h, int w, int y, int x, std::string n)
{
	height = h;
	width = w;
	startY = y;
	startX = x;
	
	name = n;
	
	win = newwin(height, width, y, x);
}

WINDOW *Panel::getwin() { return win; }
int Panel::getX() { return startX; }
int Panel::getY() { return startY; }
int Panel::getHeight() { return height; }
int Panel::getWidth() { return width; }

void Panel::movewin(int y, int x)
{
	startY = y;
	startX = x;
	
	delwin(win);
	win = newwin(height, width, startY, startX);
}

void Panel::draw()
{
	box(win, 0, 0);
	// TODO(Ryan): Print panel name at the top left of the window
}

void Panel::resize(int h, int w)
{
	height = h;
	width = w;
	wresize(win, height, width);
}


}; // namespace gelcube
