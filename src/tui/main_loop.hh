/// @file main_loop.hh
/// @author Natalie Wiggins (islifepeachy@outlook.com)
/// @brief Processes events and user input.
/// @version 0.1
/// @date 2022-08-11
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

#ifndef GELCUBE_SRC_TUI_MAIN_LOOP_HH_
#define GELCUBE_SRC_TUI_MAIN_LOOP_HH_

#include "../tui.hh"

#include <csignal>
#include <unordered_map>

#include <ncurses.h>

#ifndef NCURSES_EXT_FUNCS
#include <chrono>
#include <mutex>

namespace chrono = std::chrono;
#endif

namespace gelcube
{

class Tui::MainLoop
{
public:
    /// @brief Starts the main UI loop.
    /// Processes user input and handles window resizing until stopped,
    /// using panels from PanelManager.
    /// @throw gelcube::Tui::SizeException if the terminal is too small to fit
    ///        the panels.
    /// @throw gelcube::Tui::NoWindowException if a panel is updated and its
    ///        window has not been created.
    static void start();

    /// @brief Stops the main UI loop.
    /// Used internally as a signal handler and for exit actions.
    /// @param sig_num Signal number for sighandler_t.
    static inline void stop(int sig_num = 0) noexcept
    {
        done = true;
    }

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

    /// @brief Triggers a panel size update.
    /// Used as a signal handler if KEY_RESIZE is not supported.
    /// @param sig_num Signal number for sighandler_t.
    static inline void resized(int sig_num = 0) noexcept
    {
        was_resized = true;
    }
#endif

    static volatile sig_atomic_t done;
    static std::unordered_map<int, bool> modifiers;
#ifndef NCURSES_EXT_FUNCS
    static volatile sig_atomic_t was_resized;
    static bool invalid_resize;
    static bool uninitialized_resize;
#endif
};

}; // namespace gelcube

#endif // GELCUBE_SRC_TUI_MAIN_LOOP_HH_
