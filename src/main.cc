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
#include <vector>

#include <ncurses.h>

int main()
{
    // Enable unicode
    setlocale(LC_ALL, "");

    // Screen initialization
    initscr();
    noecho();
    cbreak();
    resizeterm(31, 98);
    curs_set(0);

    // Window initialization
    std::vector<WINDOW*> windows = {
        newwin(31, 36, 0, 0),
        newwin(5, 25, 0, 36),
        newwin(3, 25, 5, 36),
        newwin(23, 25, 8, 36),
        newwin(31, 36, 0, 61)
    };

    for (auto& window : windows)
        box(window, 0, 0);

    refresh();

    for (auto& window : windows)
        wrefresh(window);

    // Main loop
    while (getch() != (int) 'q') {};

    // End
    endwin();

    return EXIT_SUCCESS;
}
