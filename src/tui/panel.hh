/// @file panel.hh
/// @author Natalie Wiggins (islifepeachy@outlook.com)
/// @brief Wrapper for ncurses window.
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

#ifndef GELCUBE_SRC_TUI_PANEL_HH_
#define GELCUBE_SRC_TUI_PANEL_HH_

#include "../tui.hh"
#include "dimensions.hh"
#include "no_window_exception.hh"

#include <cstddef>

#include <ncurses.h>

namespace gelcube
{

class Tui::Panel
{
public:
    /// @brief Constructs a new Panel object.
    /// Initializes the panel's dimensions and name.
    /// @param dimensions Geometric dimensions for panel size and position.
    /// @param title Visible title.
    /// @param index Associated panel number in the UI.
    /// @param selected Sets the panel to (in)active.
    Panel(Dimensions* dimensions, const char* title, size_t index,
          bool selected = false);

    /// @brief Destroys the Panel object.
    /// Deletes the window associated with the panel.
    ~Panel();

    /// @brief Updates the dimensions of the panel's window.
    /// (Re)creates the window, dereferencing the dimensions passed to the
    /// constructor. Must be called at least once before refreshing the
    /// panel in order for it to be displayed.
    /// @throw gelcube::Tui::SizeException if the height or width of the
    ///        dimensions is less than 1.
    void update_dimensions();

    /// @brief Draws the border.
    /// Updates the panel's window object.
    /// @throw gelcube::Tui::NoWindowException if the window has not been
    ///        created.
    void draw();

    /// @brief Refreshes the panel contents.
    /// Updates the displayed window. Must be called for the panel to be
    /// displayed.
    /// @throw gelcube::Tui::NoWindowException if the window has not been
    ///        created.
    inline void refresh()
    {
	if (!window)
        {
            throw NoWindowException();
        }

        wrefresh(window);
    }

    /// @brief Sets the panel to active.
    /// Highlights the panel's title on the next draw.
    inline void select()
    {
        selected = true;
	curs_set(1);
    }

    /// @brief Sets the panel to inactive.
    /// Removes the highlight on the panel's title on the next draw.
    inline void deselect()
    {
        selected = false;
	curs_set(0);
    }

    /// @brief Moves the cursor within the panel
    /// @param y position to move cursor to relative to window
    /// @param x position to move cursor to relative to window 
    inline void pmove(size_t y, size_t x)
    {
	if ((curs_y > 0) && (curs_y < dimensions->height - 1)
	    && (curs_x > 0) && (curs_x < dimensions->width - 1))
	{
	    curs_y = y;
	    curs_x = x;
	}
	
	wmove(window, y, x);
    }


    /// @brief Returns x position of cursor
    /// @return Cursor X position as a size_t
    inline size_t get_curs_x()
    {
	return curs_x;
    }
    
    /// @brief Returns y position of cursor
    /// @return Cursor y position as a size_t
    inline size_t get_curs_y()
    {
	return curs_y;
    }
    
private:
    Dimensions* dimensions;
    const char* title;
    size_t index;
    bool selected = false;
    WINDOW* window = nullptr;
    size_t curs_x = 1, curs_y = 1;
};

}; // namespace gelcube

#endif // GELCUBE_SRC_TUI_PANEL_HH_
