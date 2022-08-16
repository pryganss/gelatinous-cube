/// @file panel_manager.hh
/// @author Natalie Wiggins (islifepeachy@outlook.com)
/// @brief Manages all panels.
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

#ifndef GELCUBE_SRC_TUI_PANEL_MANAGER_HH_
#define GELCUBE_SRC_TUI_PANEL_MANAGER_HH_

#include "../tui.hh"
#include "dimensions.hh"
#include "panel.hh"

#include <cstdlib>
#include <vector>

namespace gelcube
{

class Tui::PanelManager
{
public:
    /// @brief Creates all panels.
    /// Initializes panels with titles and unspecified dimensions.
    static void create();

    /// @brief Updates the dimensions of all panels to fit the current
    ///        terminal size; draws and refreshes the panels to display
    ///        them.
    /// @throw gelcube::Tui::SizeException if the terminal is too small to fit
    ///        the panels.
    /// @throw gelcube::Tui::NoWindowException if a panel is updated or
    ///        refreshed and the panel's window has not been created.
    static void update();

    /// @brief Destroys all panels.
    /// Calls the destructor of each panel in the manager.
    static inline void destroy() noexcept
    {
        panels.clear();
    }

    /// @brief Gets the index of the currently selected panel.
    /// @return Index.
    static inline size_t get_selected_index()
    {
        return selected_index;
    }

    /// @brief Gets the index of the previously selected panel.
    /// @return Index.
    static inline size_t get_last_selected_index()
    {
        return last_selected_index;
    }

    /// @brief Selects a panel.
    /// Emphasises the specified panel's title and enables the cursor. Cursor
    /// visibility will be updated after the panel's window is refreshed.
    /// @param index Index of the panel in the manager's internal panels
    ///              vector.
    /// @throw std::out_of_range if index is invalid.
    static inline void select(size_t index)
    {
        panels.at(index)->select();
        panels.at(index)->draw();
        panels.at(index)->refresh();
        selected_index = index;
        curs_set(1);
    }

    /// @brief Deselects a panel.
    /// Removes the emphasis from the specified panel's title and disables the
    /// cursor across all panels. Cursor visibility will be updated after any
    /// panel's window is refreshed.
    /// @param index Index of the panel in the manager's internal panels
    ///              vector.
    /// @throw std::out_of_range if index is invalid.
    static inline void deselect(size_t index)
    {
        panels.at(index)->deselect();
        panels.at(index)->draw();
        panels.at(index)->refresh();
        last_selected_index = index;
        curs_set(0);
    }

    static inline Panel* get_panel(size_t index)
    {
	return panels.at(index);
    }

private:
    static Dimensions large_left, middle_upper, large_right, middle_middle,
                        middle_lower;
    static std::vector<Panel*> panels;
    static size_t selected_index;
    static size_t last_selected_index;
};

}; // namespace gelcube

#endif // GELCUBE_SRC_TUI_PANEL_MANAGER_HH_
