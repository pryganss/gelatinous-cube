// ncurses window wrapper.
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

#include "dimensions.hh"
#include "panel.hh"

#include <string>

#include <ncurses.h>

namespace gelcube
{

namespace tui
{

Panel::Panel(Dimensions dimensions, const std::string& name)
{
    resize(dimensions.height, dimensions.width);
    move(dimensions.y, dimensions.x);
}

Panel::~Panel()
{
    if (window != nullptr)
        delwin(window);
}

}; // namespace tui

}; // namespace gelcube
