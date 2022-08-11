/// @file tui.hh
/// @author Natalie Wiggins (islifepeachy@outlook.com)
/// @brief Manages the Terminal User Interface.
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

namespace gelcube
{

/// @brief Manages the Terminal User Interface.
/// Handles an ncurses screen and its required procedures.
typedef class Tui
{
public:
    /// @brief Geometric dimensions for a UI object.
    /// Stores height, width, y, and x values.
    struct Dimensions;

    /// @brief Exception signifying invalid size for a UI element.
    /// Thrown if the height or width of a set of dimensions for a UI element
    /// cannot be fit into the current screen size.
    class SizeException;

    /// @brief Exception signifying an uninitialized window.
    /// Thrown if a function which references an ncurses window is called
    /// without its window being initialized.
    class NoWindowException;

    /// @brief Wrapper for ncurses window.
    /// UI element with runtime-modifyable dimensions.
    class Panel;

    /// @brief Manages all panels.
    /// Handles the creation, destruction, and dimensions of all panels.
    class PanelManager;

    /// @brief Processes events and user input.
    /// Continuously handles the UI.
    class MainLoop;

    /// @brief Starts the TUI.
    /// Initializes ncurses and starts the main UI loop.
    /// @return Exit code for the program.
    static int start() noexcept;

private:
    static Logger::Source log;
} Tui;

}; // namespace gelcube

#endif // GELCUBE_SRC_TUI_HH_
