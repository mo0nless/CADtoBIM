#pragma once

//#include "../../stdafx.h"

#include <stdexcept>
#include <string>
#include <iostream>
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

namespace Logs {

	class Logger {

	private:
		static Logger* _logger;

		// set the severity level filter necessary
		static const severity_level _severityLevelFilter = info;

		string _logFolderPath;
		src::severity_logger<severity_level> _log;


		// Private constructor so that no objects can be created.
		Logger();


	public:
		static Logger *getLogger() {
			if (!_logger) {
				_logger = new Logger();
			}

			return _logger;
		}

		void setFileNameLineAndNumber(string fileName, int lineNumber,string functionName) {
			setLoggingAttributes("File", path_to_filename(fileName));
			setLoggingAttributes("Line", lineNumber);
			setLoggingAttributes("Function", functionName);
		}

		// Set attribute and return the new value
		template<typename ValueType>
		void setLoggingAttributes(const char* name, ValueType value) {
			auto attr = logging::attribute_cast<attrs::mutable_constant<ValueType>>(logging::core::get()->get_thread_attributes()[name]);
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