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

#include <ncurses.h>

namespace gelcube
{

std::vector<WINDOW*> Tui::windows;

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
    windows = {
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

    // Main loop.
    while (getch() != static_cast<int>('q')) {};

    // End.
    endwin();

    return EXIT_SUCCESS;
}

}; // namespace gelcube
