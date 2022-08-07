// Handles message logging.
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

#include "logger.hh"

#include <iostream>

#include <boost/core/null_deleter.hpp>
#include <boost/log/core.hpp>
#include <boost/smart_ptr/make_shared_object.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>

namespace logging = boost::log;

namespace gelcube
{

boost::shared_ptr<Logger::Sink> Logger::sink;
Logger::Source Logger::source;

void Logger::init()
{
    sink = boost::make_shared<Sink>();
    boost::shared_ptr<std::ostream> stream{&std::clog, boost::null_deleter{}};
    sink->locked_backend()->add_stream(stream);
    logging::core::get()->add_sink(sink);
}

}; // namespace gelcube
