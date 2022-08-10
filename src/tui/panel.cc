/// @file panel.cc
/// @author Natalie Wiggins (islifepeachy@outlook.com)
/// @brief Wrapper for ncurses window.
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

#include "../tui.hh"

#include <string>

#include <ncurses.h>

namespace gelcube
{

Tui::Panel::Panel(Dimensions* dimensions, const std::string& label)
    : dimensions{dimensions}, label{label}
{
}

Tui::Panel::~Panel()
{
    if (window != nullptr)
    {
        delwin(window);
    }
}

void Tui::Panel::update_dimensions()
{
    if (dimensions->height > 0 && dimensions->width > 0)
    {
        if (window != nullptr)
        {
            delwin(window);
        }
        window = newwin(dimensions->height, dimensions->width,
                        dimensions->y, dimensions->x);
    }
    else
    {
        throw SizeException();
    }
}

void Tui::Panel::draw()
{
    if (!window)
    {
        throw NoWindowException();
    }

    // TODO(Ryan): Print panel label at the top left of the window.
    box(window, 0, 0); // 0, 0 used for default border characters
}

}; // namespace gelcube
