/// @file main.cc
/// @author Natalie Wiggins (islifepeachy@outlook.com)
/// @brief Entry point to Gelatinous Cube, a Dungeons & Dragons character
///        manager.
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

#include "logger.hh"
#include "options.hh"

#include <clocale>

#include <libintl.h>

namespace options = gelcube::options;
typedef gelcube::Logger Logger;

int main(int argc, char* argv[])
{
    // Initializes internationalization.
    std::setlocale(LC_ALL, "");
    textdomain("gelcube");

    // Initializes the log interface.
    Logger::init();

    // Performs procedures based on options.
    return options::parse(argc, argv);
}
