/// @file signal.hh
/// @author Natalie Wiggins (islifepeachy@outlook.com)
/// @brief Wrapper for signal handling using sigaction.
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

#ifndef GELCUBE_SRC_SIGNAL_HH_
#define GELCUBE_SRC_SIGNAL_HH_

#include <csignal>
#include <initializer_list>
#include <vector>

namespace gelcube
{

/// @brief Wrapper for signal handling.
/// Interfaces with sigaction to dynamically handle signals.
typedef class Signal
{
public:
    /// @brief Constructs a new Signal object.
    /// Registers an unmasked signal handler for each specified signal number if
    /// the previous handler didn't ignore the signal.
    /// @param handler Function to be called when the specified signals are
    ///                received.
    /// @param sig_nums Signal numbers to register with the handler and
    ///                 unregister when destroyed.
    Signal(__sighandler_t handler, std::initializer_list<int> sig_nums);

    /// @brief Destroys the Signal object.
    /// Replaces the signal handler associated with each signal number passed to
    /// the constructor with the default handler.
    ~Signal();

private:
    std::vector<int> sig_nums;
} Signal;

}; // namespace gelcube

#endif
