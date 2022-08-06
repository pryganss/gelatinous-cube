# Gelatinous Cube

Dungeons & Dragons character manager.

## Documentation

* POSIX shell commands to be run as user are denoted by `$`
* Text to be substituted in shell commands is capitalised and encapsulated in
brackets
* Visual Studio Code and Code - OSS are abbreviated to VS Code

## Requirements

* `boost` >= 1.79.0
* `gettext`
* `ncurses`

## Usage

See output of `$ gelcube --help`.

## Building

### Additional requirements

* C++17-compatible compiler with standard library (`gcc` >= 8)
* `cmake` >= 3.10

### Standalone

Targets:
* Debug:
    * `$ (mkdir -p build/debug && cd build/debug && cmake ../..  -DCMAKE_BUILD_TYPE=Debug && make)`
        * Output: `build/debug/gelcube`
* Release:
    * `$ (mkdir -p build/release && cd build/release && cmake ../.. && make)`
        * Output: `build/release/gelcube`

### VS Code

Targets:
* Debug:
    * Run Build Task (`(Debug) Build`)
        * Default keybind: `shift + ctrl/cmd + b`
        * Output: `build/debug/gelcube`
* Release:
    * Run task `(Release) Build`
        * Output: `build/release/gelcube`

## Installation

Ensure you have built the program for the release target.

### Additional requirements

* `sudo`


`$ (cd build/release && sudo make install)`

### Uninstallation

`$ (cd build/release && sudo make uninstall)`

## Code structure

* Written in C++
* Built using CMake
* Gelatinous Cube is abbreviated to `gelcube` in source code identifiers, the
build system, and the names of libraries and executables
* Lines no longer than 80 characters, unless readability is affected
* Source code located in `src/`
* Source files have the suffix `.cc`
* Header files have the suffix `.hh`
* See the [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)
for more guidelines. Exceptions to these guidelines include:
    * Tab width is 4 spaces
    * Braces, excluding for initializer lists, are placed on their own line

## Debugging

Ensure you have built the program for the debug target.

### Additional requirements

* `gdb`

### Standalone

`$ gdb build/debug/gelcube`

### VS Code

Requires the [C/C++](https://marketplace.visualstudio.com/items?itemName=ms-vscode.cpptools)
extension from the VS Code Marketplace.

* Open a source file
    * Run the default launch task (`(Debug) (gdb) Launch`)
        * Default keybind: `F5`

## Internationalization

Ensure you have built the program for the release target.

### Generating the POT template file

`$ (cd build/release && make pot-update)`

This will generate `locale/gelcube.pot`.

### Generating PO files

`$ msginit -i locale/gelcube.pot -o locale/[LANG].po -l [LOCALE])`

Edit `locale/[LANG].po` as required.

### Updating existing PO files

`$ (cd build/release && make pot-merge)`

### Generating MO files

`$ (cd build/release && make po-compile)`

## Version control

Commit messages should follow [this convention](https://www.conventionalcommits.org/)
for readability, and for any tools used in the future that depend on it.

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
