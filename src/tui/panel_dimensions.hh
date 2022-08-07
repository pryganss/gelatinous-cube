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

#ifndef GELCUBE_SRC_TUI_PANEL_DIMENSIONS_HH_
#define GELCUBE_SRC_TUI_PANEL_DIMENSIONS_HH_

#include "dimensions.hh"

namespace gelcube
{

namespace tui
{

// Manages the dimensions for all panels in the UI.
typedef struct PanelDimensions
{
    static Dimensions large_left, middle_upper, large_right, middle_middle,
                      middle_lower;

    // Updates dimensions to fit the current terminal size.
    static void update() noexcept;
} PanelDimensions;

}; // namespace tui

}; // namespace gelcube

#endif // GELCUBE_SRC_TUI_PANEL_DIMENSIONS_HH_
