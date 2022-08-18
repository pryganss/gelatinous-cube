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
#include "key_bindings.hh"
#include "panel_manager.hh"

#include <csignal>
#include <cstddef>
#include <unordered_map>

#include <ncurses.h>

class Tui::MainLoop {
public:
	/// @brief Starts the main UI loop.
	/// Processes user input and handles window resizing until stopped,
	/// using panels from PanelManager. Updates the PanelManager when
	/// called.
	/// @throw NoWindowException if a panel is updated and its window has
	/// not been created.
	static void start();

	/// @brief Stops the main UI loop.
	/// Used internally as a signal handler and for exit actions.
	/// @param sig_num Signal number for sighandler_t.
	static void stop(int sig_num = 0) noexcept
	{
		done = true;
	}

private:
	/// @brief Updates the dimensions of all panels.
	/// Sets invalid_resize to true, destroys the PanelManager's panels, and
	/// prints a message if a SizeException is thrown.
	/// @throw NoWindowException if a panel is updated or refreshed and the
	/// panel's window has not been created.
	static void try_panel_resize();

	/// @brief Enters the panel selction mode based on current modifiers.
	/// Deselects the current panel and enables the 'go' modifier in
	/// modifier_map if disabled, otherwise selects the previously
	/// selected panel and disables the 'go' modifier in modifier_map.
	static void check_start_panel_selection();

	/// @brief Selects a panel based on current modifiers.
	/// Moves the focus to a panel if the 'go' modifier is enabled in
	/// modifier_map and clears the modifier after selection.
	/// @param index Index of the panel in the PanelManager's internal
	/// panels vector.
	/// @throw std::out_of_range if index is invalid.
	static void check_select_panel(size_t index);

	static int ch;
	static volatile sig_atomic_t done;
	static std::unordered_map<int, bool> modifier_map;
	static bool invalid_resize;
};

#endif // GELCUBE_SRC_TUI_MAIN_LOOP_HH_
