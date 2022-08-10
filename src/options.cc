/// @file options.cc
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

#include "config.hh"
#include "intl.hh"
#include "logger.hh"
#include "options.hh"
#include "tui.hh"

#include <cstdlib>
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <boost/program_options/errors.hpp>
#include <boost/program_options/options_description.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/program_options/variables_map.hpp>

namespace po = boost::program_options;

namespace gelcube
{

namespace options
{

/// @brief Stores data for a program option.
/// Used as a dynamic container for boost::program_options (po::).
typedef class Option
{
public:
    /// @brief Constructs a new Option object.
    /// Stores option data for use with po::.
    /// @param long_name Long-format option name.
    /// @param description Describes the functionality of the option.
    /// @param short_name Short-format option name.
    Option(const char* long_name, const char* description,
           const char* short_name = "")
        : long_name{long_name}, description{description}, short_name{short_name}
    {
    }

    /// @brief Gets the full name of the option to add to a description.
    /// Uses the format 'LONG' or 'LONG,SHORT' for use with
    /// po::options_description::add_options.
    /// @return Full name (internal data).
    const char* name() noexcept
    {
        if (std::strlen(short_name) > 0)
        {
            std::stringstream ss_name;
            ss_name << long_name << "," << short_name;
            s_name = ss_name.str();
            return s_name.c_str();
        }
        else
        {
            return long_name;
        }
    }

    /// @brief Gets the number of occurrences of the option in a variables map.
    /// Used with a notified variables map containing parsed option data.
    /// @param vm Variables map of long-format option names to values.
    /// @return Number of occurrences.
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

Option help(
    _("help"),
    _("display this help and exit"),
    _("h"));

Option version(
    _("version"),
    _("output version information and exit"),
    _("V"));

/// @brief Shows the version string.
/// Prints version, copyright, and author information to stdout.
void show_version() noexcept
{
    std::cout << _("Gelatinous Cube ") << config::version_major << "." << config::version_minor << std::endl
              << _("Copyright (c) ") << config::version_year << _(" The Gelatinous Cube Authors.") << std::endl
              << _("License GPLv3+: GNU GPL version 3 or later <https://gnu.org/licenses/gpl.html>.") << std::endl
              << _("This is free software: you are free to change and redistribute it.") << std::endl
              << _("There is NO WARRANTY, to the extent permitted by law.") << std::endl
              << std::endl
              << _("Written by Ryan Pullinger and Natalie Wiggins.") << std::endl;
}

int parse(int argc, char* argv[]) noexcept
{
    if (argc < 1)
        return EXIT_FAILURE;

    Logger::Source log = Logger::source;

    // Declares supported options.
    std::stringstream caption;
    caption << _("Usage: ") << argv[0] << _(" [OPTION]...") << std::endl
            << _("Manage Dungeons & Dragons characters.") << std::endl
            << std::endl
            << _("Mandatory arguments to long options are mandatory for short options too");
    po::options_description desc(caption.str());
    desc.add_options()
        (options::help.name(), options::help.description)
        (options::version.name(), options::version.description);

    // Processes options.
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
        {
            return Tui::start();
        }
    }
    catch (po::unknown_option& e)
    {
        BOOST_LOG_SEV(log, LogLevel::fatal)
            << argv[0] << _(": unrecognized option '") << e.get_option_name() << _("'") << std::endl
            << _("Try '") << argv[0] << _(" --help' for more information.") << std::endl;
        return EXIT_FAILURE;
    }
}

}; // namespace options

}; // namespace gelcube
