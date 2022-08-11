/// @file dimensions.hh
/// @author Natalie Wiggins (islifepeachy@outlook.com)
/// @brief Geometric dimensions for a UI object.
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

#ifndef GELCUBE_SRC_TUI_DIMENSIONS_HH_
#define GELCUBE_SRC_TUI_DIMENSIONS_HH_

#include "../tui.hh"

namespace gelcube
{

struct Tui::Dimensions
{
    int height, width, y, x;
};

}; // namespace gelcube

#endif // GELCUBE_SRC_TUI_DIMENSIONS_HH_
