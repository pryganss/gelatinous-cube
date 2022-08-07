// Objects for managing the size and position of UI elements.
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

#ifndef GELCUBE_SRC_TUI_DIMENSIONS_HH_
#define GELCUBE_SRC_TUI_DIMENSIONS_HH_

#include <exception>

namespace gelcube
{

namespace tui
{

typedef struct Dimensions
{
    int height, width, y, x;
} Dimensions;

// Thrown if the height or width of a set of dimensions for a UI element is
// invalid.
typedef class SizeException : public std::exception
{
} SizeException;

}; // namespace tui

}; // namespace gelcube

#endif // GELCUBE_SRC_TUI_DIMENSIONS_HH_
