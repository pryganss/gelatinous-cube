/// @file size_exception.hh
/// @author Natalie Wiggins (islifepeachy@outlook.com)
/// @brief Exception signifying an invalid size for a UI element.
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

#ifndef GELCUBE_SRC_TUI_SIZE_EXCEPTION_HH_
#define GELCUBE_SRC_TUI_SIZE_EXCEPTION_HH_

#include "../tui.hh"

#include <exception>

namespace gelcube
{

class Tui::SizeException : public std::exception
{
};

} // namespace gelcube

#endif // GELCUBE_SRC_TUI_SIZE_EXCEPTION_HH_
