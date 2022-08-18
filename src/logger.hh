/// @file logger.hh
/// @author Natalie Wiggins (islifepeachy@outlook.com)
/// @brief Message log handler.
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

#ifndef GELCUBE_SRC_LOGGER_HH_
#define GELCUBE_SRC_LOGGER_HH_

#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/sinks/text_ostream_backend.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/trivial.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>

namespace b_log = boost::log;

/// @brief Handles message logging.
/// Provides a source for boost::log after initialization.
class Logger {
public:
	/// @brief Initializes the log interface.
	/// Creates the required sink and registers the ostream backend to make the
	/// source usable.
	static void init();

	typedef b_log::sources::severity_logger<int> Source;
	// Log source for use with BOOST_LOG_SEV.
	static Source source;

private:
	typedef b_log::sinks::synchronous_sink<
		b_log::sinks::text_ostream_backend> Sink;
	static boost::shared_ptr<Sink> sink;
};

// Accessible alias for trivial log severity levels.
typedef boost::log::trivial::severity_level LogLevel;

#endif // GELCUBE_SRC_LOGGER_HH_
