// Program options parser.
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

#include "config.hh"
#include "intl.hh"
#include "parse_options.hh"
#include "tui.hh"

#include <cstdlib>
#include <iostream>
#include <ostream>
#include <sstream>
#include <string>
#include <vector>

#include <boost/program_options/errors.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

namespace gelcube
{

namespace po = boost::program_options;

typedef class Option
{
public:
    Option(const char* long_name, const char* description,
           const char* short_name = nullptr)
            : long_name{long_name}, description{description},
              short_name{short_name}
    {
    }

    const char* name() noexcept
    {
        if (short_name == nullptr)
            return long_name;
        else
        {
            std::stringstream ss_name;
            ss_name << long_name << "," << short_name;
            s_name = ss_name.str();
            return s_name.c_str();
        }
    }

    inline size_t count(po::variables_map vm) const noexcept
    {
        return vm.count(long_name);
    }

    const char* long_name;
    const char* description;
    const char* short_name;

private:
    std::string s_name;
} Option;

namespace options
{

Option help(
        _("help"),
        _("display this help and exit"),
        _("h"));

Option version(
        _("version"),
        _("output version information and exit"),
        _("V"));

}; // namespace options

void show_version() noexcept
{
    std::cout << _("Gelatinous Cube ") << config::version_major << "."
                << config::version_minor << std::endl
              << _("Copyright (C) ") << config::version_year << _(" Ryan Pullinger and Natalie Wiggins.")
                << std::endl
              << _("License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>.") << std::endl
              << _("This is free software: you are free to change and redistribute it.") << std::endl
              << _("There is NO WARRANTY, to the extent permitted by law.") << std::endl
              << std::endl
              << _("Written by Ryan Pullinger and Natalie Wiggins.") << std::endl;
}

int parse_options(int argc, char* argv[]) noexcept
{
    if (argc < 1)
        return EXIT_FAILURE;

    // Declare supported options.
    std::stringstream caption;
    caption << _("Usage: ") << argv[0] << _(" [OPTION]...") << std::endl
            << _("Manage Dungeons & Dragons characters.") << std::endl
            << std::endl
            << _("Mandatory arguments to long options are mandatory for short options too");
    po::options_description desc(caption.str());
    desc.add_options()
        (options::help.name(), options::help.description)
        (options::version.name(), options::version.description);

    // Process options.
    try
    {
        po::variables_map vm;
        po::store(po::parse_command_line(argc, argv, desc), vm);
        po::notify(vm);
        if (options::help.count(vm))
        {
            std::cout << desc << std::endl;
            return EXIT_SUCCESS;
        }
        else if (options::version.count(vm))
        {
            show_version();
            return EXIT_SUCCESS;
        }
        else
            return Tui::start();
    }
    catch (po::unknown_option& e)
    {
        std::cerr << argv[0] << _(": unrecognized option '") << e.get_option_name() << _("'") << std::endl
                  << _("Try '") << argv[0] << _(" --help' for more information.") << std::endl;
        return EXIT_FAILURE;
    }
}

}; // namespace gelcube
