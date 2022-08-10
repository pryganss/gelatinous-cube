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

#include <cstddef>
#include <string>

#include <ncurses.h>

namespace gelcube
{

Tui::Panel::Panel(Dimensions* dimensions, const char* title, size_t index,
                  bool selected)
    : dimensions{dimensions}, title{title}, index{index}, selected{selected}
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

    // TODO(Natalie): Check dimensions.

    // Border.
    box(window, 0, 0); // 0, 0 used for default border characters

    // Title.
    if (selected)
    {
        wattron(window, A_STANDOUT);
    }
    mvwprintw(window, 0, 2, "%s", title);
    if (selected)
    {
        wattroff(window, A_STANDOUT);
    }

    // Index label.
    mvwprintw(window, 0, dimensions->width - 4, "[%zi]", index);
}

}; // namespace gelcube
