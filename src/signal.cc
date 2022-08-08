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

#include "signal.hh"

#include <csignal>
#include <initializer_list>

namespace gelcube
{

Signal::Signal(__sighandler_t handler, std::initializer_list<int> sig_nums)
    : sig_nums{sig_nums}
{
    struct sigaction action;
    
    action.sa_handler = handler;
    
    // Don't block signals.
    sigemptyset(&action.sa_mask);

    action.sa_flags = 0;

    struct sigaction old_action;
    for (auto& sig_num : this->sig_nums)
    {
        sigaddset(&action.sa_mask, sig_num);

        // Read old action associated with signal number.
        sigaction(sig_num, NULL, &old_action);
        // Replace the old handler if it didn't ignore the signal.
        if (old_action.sa_handler != SIG_IGN)
            sigaction(sig_num, &action, NULL);
    }
}

Signal::~Signal()
{
    struct sigaction old_action;
    for (auto& sig_num : sig_nums)
    {
        // Read old action associated with signal number.
        sigaction(sig_num, NULL, &old_action);
        // Replace the old handler with the default if it didn't ignore the
        // signal.
        if (old_action.sa_handler != SIG_IGN)
        {
            struct sigaction action;

            action.sa_handler = SIG_DFL;

            // Don't block signals.
            sigemptyset(&action.sa_mask);

            action.sa_flags = 0;

            sigaction(sig_num, &action, NULL);
        }
    }  
}

}; // namespace gelcube
