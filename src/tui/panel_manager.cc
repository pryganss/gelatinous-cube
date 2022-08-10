/// @file panel_manager.cc
/// @author Natalie Wiggins (islifepeachy@outlook.com)
/// @brief Manages all panels in the TUI.
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
#include "../tui.hh"

#include <vector>

#include <ncurses.h>

namespace gelcube
{

Tui::Dimensions Tui::PanelManager::large_left, Tui::PanelManager::middle_upper,
                Tui::PanelManager::large_right,
                Tui::PanelManager::middle_middle,
                Tui::PanelManager::middle_lower;
std::vector<Tui::Panel*> Tui::PanelManager::panels;

void Tui::PanelManager::create()
{
    panels = {
        new Panel(&large_left, _("Magic"), true),
        new Panel(&middle_upper, _("Combat")),
        new Panel(&large_right, _("Skills")),
        new Panel(&middle_middle, _("Name")),
        new Panel(&middle_lower, _("Attacks"))
    };
}

void Tui::PanelManager::update()
{
    // Height.
    large_left.height = LINES;
    middle_upper.height = LINES / 5;
    large_right.height = large_left.height;
    middle_middle.height = LINES / 7.2;
    middle_lower.height = LINES - middle_upper.height
                                - middle_middle.height;
    // Width.
    large_left.width = COLS / 2.7;
    middle_upper.width = COLS - (2 * large_left.width);
    large_right.width = large_left.width;
    middle_middle.width = middle_upper.width;
    middle_lower.width = middle_upper.width;
    // Y.
    large_left.y = 0;
    middle_upper.y = 0;
    large_right.y = 0;
    middle_middle.y = middle_upper.height;
    middle_lower.y = middle_upper.height + middle_middle.height;
    // X.
    large_left.x = 0;
    middle_upper.x = large_left.width;
    large_right.x = large_left.width + middle_upper.width;
    middle_middle.x = large_left.width;
    middle_lower.x = large_left.width;

    // Updates, (re)draws, and refreshes panels to display them.
    for (auto& panel : panels)
    {
        panel->update_dimensions();
        panel->draw();
    }
    refresh();
    for (auto& panel : panels)
    {
        panel->refresh();
    }
}

}; // namespace gelcube
