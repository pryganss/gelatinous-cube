// Processes events and user input.
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

#include "../signal.hh"
#include "../tui.hh"

#include <csignal>
#include <vector>

#include <ncurses.h>

namespace gelcube
{

volatile sig_atomic_t Tui::MainLoop::done;
#ifndef NCURSES_EXT_FUNCS
volatile sig_atomic_t Tui::MainLoop::was_resized;
#endif

void Tui::MainLoop::start()
{
    std::vector<Signal*> signals = {
        new Signal(stop, {SIGINT})
#ifndef NCURSES_EXT_FUNCS
        ,
        new Signal(resized, {SIGWINCH})
#endif
    };

    while (!done)
    {
#ifndef NCURSES_EXT_FUNCS
        // TODO(Natalie): Test and re-implment non-extended resize functionality
        // to prevent resizing from being delayed until input is received.
        if (was_resized)
            PanelManager::update();
#endif
        switch (getch())
        {
#ifdef NCURSES_EXT_FUNCS
            case KEY_RESIZE:
                PanelManager::update();
                break;
#endif
            case static_cast<int>('q'):
                stop();
                break;
        }
    }
}

}; // namespace gelcube
