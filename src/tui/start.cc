/// @file start.cc
/// @author Natalie Wiggins (islifepeachy@outlook.com)
/// @brief Initializes ncurses and starts the main UI loop.
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

#include "../intl.hh"
#include "../logger.hh"
#include "../tui.hh"
#include "main_loop.hh"
#include "panel_manager.hh"
#include "size_exception.hh"

#include <cstdlib>

#include <ncurses.h>

Logger::Source Tui::log;

int Tui::start() noexcept
{
	log = Logger::source;

	// Initialize ncurses screen.
	initscr();
	noecho();
	cbreak();

	// Initialize panels.
	PanelManager::create();

	// Handle user input and events.
	MainLoop::start();

	// End.
	PanelManager::destroy();
	endwin();

	return EXIT_SUCCESS;
}
