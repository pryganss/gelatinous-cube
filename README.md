# Gelatinous Cube

Dungeons & Dragons character manager.

## Documentation

- Shell commands to be run as user are denoted by `$`

## Building

### Requirements

- C++17-compatible compiler with standard library (`gcc` >= 8)
- `boost` >= 1.79.0
- `cmake` >= 3.10
- `gettext`
- `ncurses`

### Release

`$ (mkdir -p build && cd build && cmake .. && make)`

### Debug

`$ (mkdir -p build && cd build && cmake .. -DCMAKE_BUILD_TYPE=Debug && make)`

## Usage

`% ./build/gelcube`

## Code structure

- Written in C++
- Built using CMake
- Gelatinous Cube is abbreviated to `gelcube` in source code identifiers, the
build system, and the names of libraries and executables
- Lines no longer than 80 characters
- Source code located in `src/`
    - Source files have the suffix `.cc`
    - Header files have the suffix `.hh`
- See the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
for more guidelines. Exceptions to these guidelines include:
    - Tab width is 4 spaces
    - Braces, excluding for initializer lists, are placed on their own line

## Version control

Commit messages should follow [these conventions](https://www.conventionalcommits.org/)
for readability and for any external tools which may be used in the future that
depend on them.

## License

Copyright (C) 2022 Ryan Pullinger and Natalie Wiggins

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program. If not, see <https://www.gnu.org/licenses/>.

See `LICENSE` for more information.
