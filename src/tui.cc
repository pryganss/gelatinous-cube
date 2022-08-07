// Manages the Terminal User Interface.
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

#include "intl.hh"
#include "logger.hh"
#include "tui.hh"
#include "tui/panel_dimensions.hh"
#include "tui/panel.hh"

#include <cstdlib>
#include <vector>

#include <ncurses.h>

namespace gelcube
{

namespace tui
{

std::vector<Panel*> panels;

int start() noexcept
{
    Logger::Source log = Logger::source;

    // Screen initialization.
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    // Panel initialization.
    PanelDimensions::update();
    try
    {
        panels = {
            new Panel(PanelDimensions::large_left, "1"),
            new Panel(PanelDimensions::middle_upper, "2"),
            new Panel(PanelDimensions::large_right, "3"),
            new Panel(PanelDimensions::middle_middle, "4"),
            new Panel(PanelDimensions::middle_lower, "5")
        };
    }
    catch (SizeException& e)
    {
        BOOST_LOG_SEV(log, LogLevel::fatal)
            << _("Terminal too small to fit user interface.");
        return EXIT_FAILURE;
    }

    for (auto& panel : panels)
        panel->draw();

    refresh();

    for (auto& panel : panels)
        panel->refresh();

    // Main loop.
    // TODO(Natalie): Check for terminal resize and update panel dimensions
    // accordingly.
    while (getch() != static_cast<int>('q')) {};

    // End.
    panels.clear();
    endwin();

    return EXIT_SUCCESS;
}

}; // namespace tui

}; // namespace gelcube
