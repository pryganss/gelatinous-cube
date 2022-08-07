// Manages the dimensions for all panels in the UI.
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

#include "panel_dimensions.hh"

#include <ncurses.h>

namespace gelcube
{

namespace tui
{

Dimensions PanelDimensions::large_left, PanelDimensions::middle_upper,
           PanelDimensions::large_right, PanelDimensions::middle_middle,
           PanelDimensions::middle_lower;

void PanelDimensions::update() noexcept
{
    // Height
    large_left.height = LINES;
    middle_upper.height = LINES / 3.5;
    large_right.height = large_left.height;
    middle_middle.height = LINES / 4.5;
    middle_lower.height = LINES - middle_upper.height
                                - middle_middle.height;
    // Width
    large_left.width = COLS / 2.7;
    middle_upper.width = COLS - (2 * large_left.width);
    large_right.width = large_left.width;
    middle_middle.width = middle_upper.width;
    middle_lower.width = middle_upper.width;
    // Y
    large_left.y = 0;
    middle_upper.y = 0;
    large_right.y = 0;
    middle_middle.y = middle_upper.height;
    middle_lower.y = middle_upper.height + middle_middle.height;
    // X
    large_left.x = 0;
    middle_upper.x = large_left.width;
    large_right.x = large_left.width + middle_upper.width;
    middle_middle.x = large_left.width;
    middle_lower.x = large_left.width;
}

}; // namespace tui

}; // namespace gelcube