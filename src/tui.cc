// Terminal User Interface.
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

#include "tui.hh"

#include <cstdlib>
#include <string>
#include <vector>

#include <ncurses.h>

namespace gelcube
{

class Panel
{
public:
    Panel(int height, int width, int y, int x, const std::string& name)
        : height{height}, width{width}, y{y}, x{x}, name{name},
          window{newwin(height, width, y, x)}
    {
    }

    ~Panel()
    {
        delwin(window);
    }

    inline const WINDOW* get_window() const noexcept
    {
        return window;
    }

    inline int get_height() const noexcept
    {
        return height;
    }

    inline int get_width() const noexcept
    {
        return width;
    }
    
    inline int get_y() const noexcept
    {
        return y;
    }

    inline int get_x() const noexcept
    {
        return x;
    }

    inline const std::string get_name() const noexcept
    {
        return name;
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

    void move(int y, int x) noexcept
    {
        this->y = y;
        this->x = x;
        delwin(window);
        window = newwin(height, width, y, x);
    }    

    void resize(int height, int width) noexcept
    {
        this->height = height;
        this->width = width;
        wresize(window, height, width);
    }

private:
    int height, width, y, x;
    std::string name;
    WINDOW* window;
};

std::vector<Panel*> Tui::panels;

int Tui::start() noexcept
{
    // Screen initialization.
    // TODO(Natalie): Remove forced buffer size; we'll need to update window
    // initialization.
    initscr();
    noecho();
    cbreak();
    resizeterm(31, 98);
    curs_set(0);

    // Window initialization.
    // TODO(Natalie): Implement dynamic assignment of window sizes.
    panels = {
        new Panel(31, 36, 0, 0, "1"),
        new Panel(5, 25, 0, 36, "2"),
        new Panel(3, 25, 5, 36, "3"),
        new Panel(23, 25, 8, 36, "4"),
        new Panel(31, 36, 0, 61, "5")
    };

    for (auto& panel : panels)
        panel->draw();

    refresh();

    for (auto& panel : panels)
        panel->refresh();

    // Main loop.
    while (getch() != static_cast<int>('q')) {};

    // End.
    panels.clear();
    endwin();

    return EXIT_SUCCESS;
}

}; // namespace gelcube
