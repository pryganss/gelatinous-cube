// Entry point to Gelatinous Cube, a Dungeons & Dragons character manager.
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

#include <clocale>
#include <cstdlib>

#include <ncurses.h>

int main()
{
	int i;
	WINDOW *windows[5];
  
	setlocale(LC_ALL, "");

	// screen initialization
	initscr();
	noecho();
	resizeterm(31, 98);
	curs_set(0);
	cbreak();

	// windows initialization
	windows[0] = newwin(31, 36, 0, 0);
	windows[1] = newwin(5, 25, 0, 36);
	windows[2] = newwin(3, 25, 5, 36);
	windows[3] = newwin(23, 25, 8, 36);
	windows[4] = newwin(31, 36, 0, 61);

	for (i = 0; i < 5; i++)
		box(windows[i], 0, 0);
	
	refresh();
	for (i = 0; i < 5; i++)
		wrefresh(windows[i]);
	
	while (getch() != (int)'q'); // wiat for the user to press q
	
	
	// END
    endwin();

    return EXIT_SUCCESS;
}
