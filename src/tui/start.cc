// Starts the Terminal User Interface.
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

#include "../intl.hh"
#include "../logger.hh"
#include "../tui.hh"

#include <cstdlib>

#include <ncurses.h>

namespace gelcube
{

Logger::Source Tui::log;

int Tui::start() noexcept
{
    log = Logger::source;

    // Screen initialization.
    initscr();
    noecho();
    cbreak();
    curs_set(0);

    // Panel initialization.
    PanelManager::create();
    try
    {
        PanelManager::update();
    }
    catch (SizeException& e)
    {
        BOOST_LOG_SEV(log, LogLevel::fatal)
            << _("Terminal too small to fit user interface.");
        return EXIT_FAILURE;
    }

    // Process user input and UI events.
    try
    {
        MainLoop::start();
    }
    catch (SizeException& e)
    {
        BOOST_LOG_SEV(log, LogLevel::fatal)
            << _("Terminal too small to fit user interface.");
        return EXIT_FAILURE;
    }

    // End.
    PanelManager::destroy();
    endwin();

    return EXIT_SUCCESS;
}

}; // namespace gelcube
