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
#include "position.hh"
#include "size_exception.hh"

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
    /// @param index Panel number.
    Panel(Dimensions* dimensions, const char* title, size_t index);

    /// @brief Destroys the Panel object.
    /// Deletes the window associated with the panel.
    ~Panel();

    /// @brief (Re)creates the panel's window.
    /// Dereferences the dimensions passed to the constructor. Must be called at
    /// least once before refreshing the panel in order for it to be displayed.
    /// @throw gelcube::Tui::SizeException if the height or width of the
    ///        dimensions is less than 1.
    void create_window();

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
    void refresh()
    {
	    if (!window)
        {
            throw NoWindowException();
        }

        wrefresh(window);
    }

    /// @brief Gets the selection status of the panel.
    /// @return true if currently selected.
    bool is_selected() const noexcept
    {
        return selected;
    }

    /// @brief Sets the panel to active.
    /// Moves focus to the panel on the next draw.
    void select() noexcept
    {
        selected = true;
    }

    /// @brief Sets the panel to inactive.
    /// Removes the focus from the panel on the next draw.
    void deselect() noexcept
    {
        selected = false;
    }

    /// @brief Enables the visibility of the index label.
    void enable_index_label() noexcept
    {
        index_label_enabled = true;
    }

    /// @brief Disables the visibility of the index label.
    void disable_index_label() noexcept
    {
        index_label_enabled = false;
    }

    /// @brief Sets the cursor position within the panel.
    /// The cursor position, relative to the upper left-hand corner of the
    /// panel's window, will be updated on the next draw.
    /// @param position New coordinates relative to the panel's window.
    /// @throw gelcube::Tui::SizeException if the position does not fit within
    ///        panel's dimensions.
    void set_cursor_position(const Position& position)
    {
        if (position.y < 1 || position.y >= dimensions->height - 1
            || position.x < 1 || position.x >= dimensions->height - 1)
        {
            throw SizeException();
        }

        cursor_position = position;
    }

    /// @brief Gets the cursor position.
    /// @return Current position of the cursor relative to the upper left-hand
    ///         corner of the panel's window.
    const Position& get_cursor_position() const noexcept
    {
        return cursor_position;
    }

private:
    static attr_t selected_title_attributes;
    Dimensions* dimensions;
    const char* title;
    size_t index;
    bool selected = false;
    bool index_label_enabled = false;
    WINDOW* window = nullptr;
    Position cursor_position = {1, 2};
};

}; // namespace gelcube

#endif // GELCUBE_SRC_TUI_PANEL_HH_
