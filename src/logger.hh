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

#ifndef GELCUBE_SRC_LOGGER_HH_
#define GELCUBE_SRC_LOGGER_HH_

#include <boost/log/core.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/trivial.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>

namespace logging = boost::log;
namespace sinks = boost::log::sinks;
namespace sources = boost::log::sources;

namespace gelcube
{

// Handles message logging.
typedef class Logger
{
public:
    static void init();

    typedef sources::severity_logger<int> Source;
    static Source source;
private:
    typedef sinks::synchronous_sink<sinks::text_ostream_backend> Sink;
    static boost::shared_ptr<Sink> sink;
} Logger;

typedef boost::log::trivial::severity_level LogLevel;

}; // namespace gelcube

#endif // GELCUBE_SRC_LOGGER_HH_