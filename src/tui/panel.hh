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

#ifndef GELCUBE_SRC_TUI_PANEL_HH_
#define GELCUBE_SRC_TUI_PANEL_HH_

#include "dimensions.hh"

#include <string>

#include <ncurses.h>

namespace gelcube
{

namespace tui
{

// ncurses window wrapper.
typedef class Panel
{
public:
    // Creates a new panel and its window. Throws a SizeException if the
    // specified height or width in the Dimensions object is less than 1.
    Panel(Dimensions dimensions, const std::string& name);

    // Deletes the window associated with the panel.
    ~Panel();

    // Throws a SizeException if the specified height or width is less than 1.
    inline void resize(int height, int width)
    {
        if (height > 0 && width > 0)
        {
            this->dimensions.height = height;
            this->dimensions.width = width;
            wresize(window, dimensions.height, dimensions.width);
        }
        else
        {
            throw SizeException();
        }
    }

    inline void move(int y, int x) noexcept
    {
        this->dimensions.y = y;
        this->dimensions.x = x;
        if (window != nullptr)
            delwin(window);
        window = newwin(dimensions.height, dimensions.width, dimensions.y,
                        dimensions.x);
    }

    inline void draw() noexcept
    {
        box(window, 0, 0); // 0, 0 used for default border characters
        // TODO(Ryan): Print panel name at the top left of the window
    }

    inline void refresh() noexcept
    {
        wrefresh(window);
    }

private:
    Dimensions dimensions;
    std::string name;
    WINDOW* window = nullptr;
} Panel;

}; // namespace tui

}; // namespace gelcube

#endif // GELCUBE_SRC_TUI_PANEL_HH_
