/// @file tui.hh
/// @author Natalie Wiggins (islifepeachy@outlook.com)
/// @brief Terminal User Interface manager.
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

#ifndef GELCUBE_SRC_TUI_HH_
#define GELCUBE_SRC_TUI_HH_

#include "logger.hh"

#include <csignal>
#include <cstddef>
#include <exception>
#include <string>
#include <vector>

#include <ncurses.h>

#ifndef NCURSES_EXT_FUNCS
#include <chrono>
#include <mutex>

namespace chrono = std::chrono;
#endif

namespace gelcube
{

/// @brief Manages the Terminal User Interface.
/// Handles an ncurses screen and its required procedures.
typedef class Tui
{
public:
    /// @brief Geometric dimensions for a UI object.
    /// Stores height, width, y, and x values.
    typedef struct Dimensions
    {
        int height, width, y, x;
    } Dimensions;

    /// @brief Exception signifying invalid size for a UI element.
    /// Thrown if the height or width of a set of dimensions for a UI element
    /// cannot be fit into the current screen size.
    typedef class SizeException : public std::exception
    {
    } SizeException;

    /// @brief Exception signifying an uninitialized window.
    /// Thrown if a function which references an ncurses window is called
    /// without its window being initialized.
    typedef class NoWindowException : public std::exception
    {
    } NoWindowException;

    /// @brief Wrapper for ncurses window.
    /// UI element using dimensions modifyable at runtime.
    typedef class Panel
    {
    public:
        /// @brief Constructs a new Panel object.
        /// Initializes the panel's dimensions and name.
        /// @param dimensions Geometric dimensions for panel size and position.
        /// @param title Visible title.
        /// @param index Associated panel number in the UI.
        /// @param selected Sets the panel to (in)active.
        Panel(Dimensions* dimensions, const char* title, size_t index, bool selected = false);

        /// @brief Destroys the Panel object.
        /// Deletes the window associated with the panel.
        ~Panel();

        /// @brief Updates the dimensions of the panel's window.
        /// (Re)creates the window, dereferencing the dimensions passed to the
        /// constructor. Must be called at least once before refreshing the
        /// panel in order for it to be displayed. Throws a SizeException if the
        /// height or width of the dimensions is less than 1.
        void update_dimensions();

        /// @brief Draws the border.
        /// Updates the panel's window object. Throws a NoWindowException if the
        /// window has not been created.
        void draw();

        /// @brief Refreshes the panel contents.
        /// Updates the displayed window. Must be called for the panel to be
        /// displayed. Thorw a NoWindowException if the window has not been
        /// created.
        inline void refresh()
        {
            if (!window)
            {
                throw NoWindowException();
            }

            wrefresh(window);
        }

        /// @brief Sets the panel to active.
        /// Highlights the panel's title on the next draw.
        inline void select()
        {
            selected = true;
        }

        /// @brief Sets the panel to inactive.
        /// Removes the highlight on the panel's title on the next draw.
        inline void deselect()
        {
            selected = false;
        }

    private:
        Dimensions* dimensions;
        const char* title;
        WINDOW* window = nullptr;
        size_t index;
        bool selected = false;
    } Panel;

    /// @brief Manages all panels.
    /// Handles the creation, destruction, and dimensions of all panels.
    typedef class PanelManager
    {
    public:
        /// @brief Creates all panels.
        /// Initializes panels with titles and unspecified dimensions.
        static void create();

        /// @brief Updates the dimensions of all panels to fit the current
        ///        terminal size; draws and refreshes the panels to display
        ///        them.
        /// Throws a SizeException if the terminal is too small to fit the
        /// panels; throws a NoWindowException if a panel is updated or
        /// refreshed and the panel's window has not been created.
        static void update();

        /// @brief Destroys all panels.
        /// Calls the destructor of each panel in the manager.
        static inline void destroy() noexcept
        {
            panels.clear();
        }

    private:
        static Dimensions large_left, middle_upper, large_right, middle_middle,
                          middle_lower;
        static std::vector<Panel*> panels;
    } PanelManager;

    /// @brief Processes events and user input.
    /// Continuously handles the UI.
    typedef class MainLoop
    {
    public:
        /// @brief Starts the main UI loop.
        /// Processes user input and handles window resizing until stopped,
        /// using panels from PanelManager. Throws a SizeException if the
        /// terminal is too small to fit the panels; throws a NoWindowException
        /// if a panel is updated and its window has not been created.
        static void start();

        /// @brief Stops the main UI loop.
        /// Used internally as a signal handler and for exit actions.
        /// @param sig_num Signal number for sighandler_t.
        static inline void stop(int sig_num = 0) noexcept
        {
            done = true;
        }

#ifndef NCURSES_EXT_FUNCS
        /// @brief Triggers a panel size update.
        /// Used internally as a signal handler if KEY_RESIZE is not
        /// supported.
        /// @param sig_num Signal number for sighandler_t.
        static inline void resized(int sig_num = 0) noexcept
        {
            was_resized = true;
        }
#endif

    private:
#ifndef NCURSES_EXT_FUNCS
        /// @brief Polls to check if the SIGWINCH signal was received and
        ///        triggers a panel size update accordingly.
        /// Used on a separate thread if KEY_RESIZE is not supported. Stops the
        /// loop and: sets invalid_resize to true if PanelManager throws a
        /// SizeException; sets uninitialized_resize if PanelManager throws a
        /// NoWindowException.
        /// @param mutex Timed mutex used to lock thread when sleeping.
        /// @param lock_duration Duration to lock the thread after each poll.
        static void poll_resize(std::timed_mutex* mutex,
                                chrono::milliseconds lock_duration) noexcept;
#endif

        static volatile sig_atomic_t done;
#ifndef NCURSES_EXT_FUNCS
        static volatile sig_atomic_t was_resized;
        static bool invalid_resize;
        static bool uninitialized_resize;
#endif
    } MainLoop;

    /// @brief Starts the TUI.
    /// Initializes ncurses and starts the main UI loop.
    /// @return int Exit code for the program.
    static int start() noexcept;

private:
    static Logger::Source log;
} Tui;

}; // namespace gelcube

#endif // GELCUBE_SRC_TUI_HH_
