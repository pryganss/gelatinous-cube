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

#include "logger.hh"

#include <csignal>
#include <exception>
#include <string>
#include <vector>
#ifndef NCURSES_EXT_FUNCS
#include <mutex>
#endif

#include <ncurses.h>

namespace gelcube
{

// Manages the Terminal User Interface.
typedef class Tui
{
public:
    typedef struct Dimensions
    {
        int height, width, y, x;
    } Dimensions;

    // Thrown if the height or width of a set of dimensions for a UI element is
    // invalid.
    typedef class SizeException : public std::exception
    {
    } SizeException;

    // Wrapper for ncurses window.
    typedef class Panel
    {
    public:
        Panel(Dimensions* dimensions, const std::string& name);

        // Deletes the window associated with the panel.
        ~Panel();

        // Updates the dimensions of the window associated with the panel from
        // the dimensions passed to the constructor. Throws a SizeException if
        // the height or width of the dimensions is less than 1.
        inline void update_dimensions()
        {
            if (dimensions->height > 0 && dimensions->width > 0)
            {
                if (window != nullptr)
                    delwin(window);
                window = newwin(dimensions->height, dimensions->width,
                                dimensions->y, dimensions->x);
            }
            else
            {
                throw SizeException();
            }
        }

        inline void draw() noexcept
        {
            box(window, 0, 0); // 0, 0 used for default border characters
            // TODO(Ryan): Print panel name at the top left of the window
        }

        inline void refresh() noexcept
        {
            wrefresh(window);
        }

    private:
        Dimensions* dimensions;
        std::string name;
        WINDOW* window = nullptr;
    } Panel;

    // Manages all panels.
    typedef class PanelManager
    {
    public:
        // Creates all panels.
        static void create();

        // Updates dimensions of all panels to fit the current terminal size.
        // Throws a SizeException if the terminal is too small to fit the
        // panels.
        static void update();

        // Deletes all panels.
        static inline void destroy() noexcept
        {
            panels.clear();
        }

    private:
        static Dimensions large_left, middle_upper, large_right, middle_middle,
                          middle_lower;
        static std::vector<Panel*> panels;
    } PanelManager;

    // Processes events and user input.
    typedef class MainLoop
    {
    public:
        // Throws a SizeException if the terminal is too small to fit the
        // panels.
        static void start();

        static inline void stop(int sig_num = 0) noexcept
        {
            done = true;
        }

#ifndef NCURSES_EXT_FUNCS
        // Signal handler for window resize for when KEY_RESIZE is not supported.
        static inline void resized(int sig_num = 0) noexcept
        {
            was_resized = true;
        }
#endif

    private:
#ifndef NCURSES_EXT_FUNCS
        // Polls to check if the SIGWINCH signal was received and triggers
        // panels to resize for when KEY_RESIZE is not supported. Stops the loop
        // and sets resize_failed if the terminal is too small to fit the panels.
        static void poll_resize(std::timed_mutex* mutex);
#endif

        static volatile sig_atomic_t done;
#ifndef NCURSES_EXT_FUNCS
        static volatile sig_atomic_t was_resized;
        static bool resize_failed;
#endif
    } MainLoop;

    // Initializes ncurses and starts the main UI loop. Returns an exit code for
    // the program.
    static int start() noexcept;

private:
    static Logger::Source log;
} Tui;

}; // namespace gelcube

#endif // GELCUBE_SRC_TUI_HH_
