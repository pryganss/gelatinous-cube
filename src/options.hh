/// @file options.hh
/// @author Natalie Wiggins (islifepeachy@outlook.com)
/// @brief Program options parser.
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

#ifndef GELCUBE_SRC_OPTIONS_HH_
#define GELCUBE_SRC_OPTIONS_HH_

namespace gelcube
{

/// @brief Parses program options.
/// Performs required procedures based on options given via the command line.
/// @param argc Number of arguments.
/// @param argv Array of arguments.
/// @return Exit code for the program.
int parse_options(int argc, char* argv[]) noexcept;

}; // namespace gelcube

#endif // GELCUBE_SRC_OPTIONS_HH_
