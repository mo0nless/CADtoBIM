#pragma once


#include <stdexcept>
#include <string>
#include <iostream>
#include <mutex>

#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>
#include <boost/smart_ptr/shared_ptr.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include <boost/log/common.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/attributes.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sinks/sync_frontend.hpp>
#include <boost/log/utility/setup/common_attributes.hpp>

#include <boost/log/core.hpp>
#include <boost/log/trivial.hpp>
#include <boost/log/expressions.hpp>
#include <boost/log/sinks/text_file_backend.hpp>
#include <boost/log/utility/setup/file.hpp>
#include <boost/log/sources/severity_logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

#include "../../common/models/headers/SessionManager.h"

namespace logging = boost::log;
namespace attrs = boost::log::attributes;
namespace src = boost::log::sources;
namespace sinks = boost::log::sinks;
namespace expr = boost::log::expressions;
namespace keywords = boost::log::keywords;

using boost::shared_ptr;

using namespace std;
using namespace logging::trivial;


namespace Logging 
{

	class Logger {

	private:
		static Logger* _logger;

		static once_flag initInstanceFlag;

		static void initLogger() {
			_logger = new Logger();
		}

		// set the severity level filter necessary
		static const severity_level _severityLevelFilter = debug;

		src::severity_logger<severity_level> _log;


		// Private constructor so that no objects can be created.
		Logger();

		mutable boost::shared_mutex _mutex;

		template<typename ValueType>
		using shared_mc = attrs::mutable_constant<
			ValueType,                                  // attribute value type
			boost::shared_mutex,						// synchronization primitive
			boost::unique_lock< boost::shared_mutex >,  // exclusive lock type
			boost::shared_lock< boost::shared_mutex >   // shared lock type
		>;

	public:
		static Logger *getLogger() {
			call_once(initInstanceFlag, &Logger::initLogger);

			return _logger;
		}

		void setFileNameLineAndNumber(string fileName, int lineNumber,string functionName) {
			boost::unique_lock<boost::shared_mutex> guard(_mutex);
			string threadId = boost::lexical_cast<string>(boost::this_thread::get_id());
			setLoggingAttributes("Thread", "Thread ID: " + threadId);
			setLoggingAttributes("File", path_to_filename(fileName));
			setLoggingAttributes("Line", lineNumber);
			setLoggingAttributes("Function", functionName);
		}

		// Set attribute and return the new value
		template<typename ValueType>
		void setLoggingAttributes(const char* name, ValueType value) {
			auto name_attr = logging::core::get()->get_global_attributes()[name];
			auto attr = logging::attribute_cast<shared_mc<ValueType>>(name_attr);
			attr.set(value);
		}

		// Convert file path to only the filename
		std::string path_to_filename(std::string path) {
			return path.substr(path.find_last_of("/\\") + 1);
		}

		void logInfo(string fileName, int lineNumber,string functionName, string infoMessage = "");

		void logDebug(string fileName, int lineNumber, string functionName, string debugMessage = "");

		void logWarning(string fileName, int lineNumber, string functionName, string warningMessage = "");

		void logError(string fileName, int lineNumber, string functionName, string errorMessage = "");

		void logError(string fileName, int lineNumber, string functionName,exception& ex, string errorMessage = "");

		void logFatal(string fileName, int lineNumber, string functionName, string fatalMessage = "");

		void logFatal(string fileName, int lineNumber, string functionName, exception& ex, string fatalMessage = "");

	};
}