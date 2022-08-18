/// @file main_loop.cc
/// @author Natalie Wiggins (islifepeachy@outlook.com)
/// @brief Processes events and user input.
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
#include "../signal.hh"
#include "key_bindings.hh"
#include "main_loop.hh"
#include "panel_manager.hh"

#include <csignal>
#include <unordered_map>
#include <vector>

#include <ncurses.h>

volatile sig_atomic_t Tui::MainLoop::done = false;
bool Tui::MainLoop::invalid_resize = false;
std::unordered_map<int, bool> Tui::MainLoop::modifier_map;

void Tui::MainLoop::start()
{
	std::vector<Signal*> signals = {new Signal(stop, {SIGINT})};

	try_panel_resize();

	int ch;
	while (!done) {
		ch = getch();
		if (!invalid_resize) {
			switch (ch) {
			// Resizes panels.
			case KEY_RESIZE:
				try_panel_resize();
				break;

			// Exits the loop.
			case key_bindings::quit:
				stop();
				break;

			// Enters panel selection mode.
			case key_bindings::modifiers::go:
				check_start_panel_selection();
				break;

			// Selects the current panel by index.
			case static_cast<int>('1'):
				check_select_panel(0);
				break;
			case static_cast<int>('2'):
				check_select_panel(1);
				break;
			case static_cast<int>('3'):
				check_select_panel(2);
				break;
			case static_cast<int>('4'):
				check_select_panel(3);
				break;
			case static_cast<int>('5'):
				check_select_panel(4);
				break;

			// Clears modifiers.
			default:
				check_select_panel(
					PanelManager::get_last_selected_index());
				break;
			}
		} else if (ch == KEY_RESIZE) {
			// Recreates and updates panels if the last resize operation failed.
			try {
				PanelManager::create();
				PanelManager::update_dimensions();
				PanelManager::render();
				invalid_resize = false;
			} catch (SizeException& e) {
				PanelManager::destroy();
			}
		}
	}
}

void Tui::MainLoop::try_panel_resize()
{
	try {
		PanelManager::update_dimensions();
		PanelManager::render();
	} catch (SizeException& e) {
		invalid_resize = true;
		PanelManager::destroy();
		mvprintw(0, 0, _("Terminal too small to fit user interface."));
	}
}

void Tui::MainLoop::check_start_panel_selection()
{
	if (!modifier_map[key_bindings::modifiers::go]) {
		PanelManager::enable_index_labels();
		PanelManager::deselect(PanelManager::get_last_selected_index());
		PanelManager::render();
		curs_set(0);
		modifier_map[key_bindings::modifiers::go] = true;
	} else {
		PanelManager::disable_index_labels();
		PanelManager::select(PanelManager::get_last_selected_index());
		PanelManager::render();
		curs_set(1);
		modifier_map[key_bindings::modifiers::go] = false;
	}
}

void Tui::MainLoop::check_select_panel(size_t index)
{
	if (modifier_map[key_bindings::modifiers::go]) {
		PanelManager::disable_index_labels();
		PanelManager::select(index);
		PanelManager::render();
		curs_set(1);
		modifier_map[key_bindings::modifiers::go] = false;
	}
}
