/// @file main_loop.cc
/// @author Natalie Wiggins (islifepeachy@outlook.com)
/// @brief Continuous TUI event and input handler.
/// @version 0.1
/// @date 2022-08-10
/// 
/// @copyright Copyright (c) 2022 The Gelatinous Cube Authors.
/// This program is free software: you can redistribute it and/or modify
/// it under the terms of the GNU General Public License as published by
/// the Free Software Foundation, either version 3 of the License, or
/// (at your option) any later version.
/// 
/// This program is distributed in the hope that it will be useful,
/// but WITHOUT ANY WARRANTY; without even the implied warranty of
/// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
/// GNU General Public License for more details.
/// 
/// You should have received a copy of the GNU General Public License
/// along with this program. If not, see <https://www.gnu.org/licenses/>.

#include "../signal.hh"
#include "../tui.hh"

#include <csignal>
#include <unordered_map>
#include <vector>

#include <ncurses.h>

#ifndef NCURSES_EXT_FUNCS
#include <chrono>
#include <mutex>
#include <thread>

namespace chrono = std::chrono;
#endif

namespace gelcube
{

volatile sig_atomic_t Tui::MainLoop::done = false;
std::unordered_map<int, bool> Tui::MainLoop::modifiers;

#ifndef NCURSES_EXT_FUNCS
volatile sig_atomic_t Tui::MainLoop::was_resized = false;
bool Tui::MainLoop::invalid_resize = false;
bool Tui::MainLoop::uninitialized_resize = false;
#endif

void Tui::MainLoop::start()
{
    // TODO(Natalie): Verify window resizing works if ncurses extended
    // functions, and by extension, KEY_RESIZE, are not supported.

    std::vector<Signal*> signals = {
        new Signal(stop, {SIGINT}),
#ifndef NCURSES_EXT_FUNCS
        new Signal(resized, {SIGWINCH})
#endif
    };

#ifndef NCURSES_EXT_FUNCS
    std::timed_mutex poll_resize_mutex;
    std::thread poll_resize_thread(poll_resize, &poll_resize_mutex,
                                   chrono::milliseconds(200));
#endif

    while (!done)
    {
        switch (getch())
        {
#ifdef NCURSES_EXT_FUNCS
        case KEY_RESIZE:
            PanelManager::update();
            break;
#endif
        // Quit.
        case static_cast<int>('q'):
            stop();
            break;

        // Go to panel.
        case static_cast<int>('g'):
            modifiers[static_cast<int>('g')] = true;
            PanelManager::deselect(PanelManager::get_selected_index());
            break;
        case static_cast<int>('1'):
            if (modifiers[static_cast<int>('g')])
            {
                PanelManager::select(0);
                modifiers[static_cast<int>('g')] = false;
            }
            break;
        case static_cast<int>('2'):
            if (modifiers[static_cast<int>('g')])
            {
                PanelManager::select(1);
                modifiers[static_cast<int>('g')] = false;
            }
            break;
        case static_cast<int>('3'):
            if (modifiers[static_cast<int>('g')])
            {
                PanelManager::select(2);
                modifiers[static_cast<int>('g')] = false;
            }
            break;
        case static_cast<int>('4'):
            if (modifiers[static_cast<int>('g')])
            {
                PanelManager::select(3);
                modifiers[static_cast<int>('g')] = false;
            }
            break;
        case static_cast<int>('5'):
            if (modifiers[static_cast<int>('g')])
            {
                PanelManager::select(4);
                modifiers[static_cast<int>('g')] = false;
            }
            break;
        
        // Clears modifiers.
        default:
            if (modifiers[static_cast<int>('g')])
            {
                PanelManager::select(PanelManager::get_last_selected_index());
                modifiers[static_cast<int>('g')] = false;
            }
            break;
        }
    }

#ifndef NCURSES_EXT_FUNCS
    poll_resize_mutex.unlock();
    poll_resize_thread.join();
    if (invalid_resize)
    {
        throw SizeException();
    }
    else if (uninitialized_resize)
    {
        throw NoWindowException();
    }
#endif
}

#ifndef NCURSES_EXT_FUNCS
void Tui::MainLoop::poll_resize(std::timed_mutex* mutex,
                                chrono::milliseconds lock_duration) noexcept
{
    while (!done)
    {
        if (was_resized)
        {
            try
            {
                PanelManager::update();
                was_resized = false;
                mutex->try_lock_for(chrono::milliseconds(lock_duration));
            }
            catch (SizeException& e)
            {
                invalid_resize = true;
                stop();
            }
            catch (NoWindowException& e)
            {
                uninitialized_resize = true;
                stop();
            }
        }
    }
}
#endif

}; // namespace gelcube
