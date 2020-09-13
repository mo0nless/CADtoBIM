#include "..\headers\Logger.h"

namespace Logs {


	Logger *Logger::_logger = 0;


	Logger::Logger()
	{

		try
		{

			string logsOutputFolderPath = SessionManager::getInstance()->getCurrentDayLogsFolderPath();
			// Create a log file sink
			typedef sinks::synchronous_sink<sinks::text_file_backend > file_sink;
			boost::shared_ptr< file_sink > sink(new file_sink(
				keywords::file_name = logsOutputFolderPath+"\\file_%Y-%m-%d_%H-%M-%S.%N.log",      // file name pattern
				keywords::rotation_size = 16384,                // rotation size, in characters
				keywords::auto_flush = true
			));

			// Set up where the rotated files will be stored
			sink->locked_backend()->set_file_collector(sinks::file::make_collector(
				keywords::target = logsOutputFolderPath,                          // where to store rotated files
				keywords::max_size = 16 * 1024 * 1024,              // maximum total size of the stored files, in bytes
				keywords::min_free_space = 100 * 1024 * 1024        // minimum free space on the drive, in bytes
			));

			// Upon restart, scan the target directory for files matching the file_name pattern
			sink->locked_backend()->scan_for_files();


			sink->set_formatter
			(
				expr::format("%1%: [%2%]: <%3%> [%4% : %5% : %6%] - %7%")
				% expr::attr<unsigned int>("RecordID")
				% expr::attr<boost::posix_time::ptime>("TimeStamp")
				% severity
				% expr::attr<string>("File")
				% expr::attr<int>("Line")
				% expr::attr<string>("Function")
				% expr::smessage
			);

			// Add it to the core
			logging::core::get()->add_sink(sink);
	
			// Add some attributes too
			logging::core::get()->add_global_attribute("TimeStamp", attrs::local_clock());
			logging::core::get()->add_global_attribute("RecordID", attrs::counter<unsigned int>());
			// New attributes that hold filename and line number
			logging::core::get()->add_thread_attribute("File", attrs::mutable_constant<std::string>(""));
			logging::core::get()->add_thread_attribute("Line", attrs::mutable_constant<int>(0));
			logging::core::get()->add_thread_attribute("Function", attrs::mutable_constant<std::string>(""));


			// set filter
			logging::core::get()->set_filter
			(
				severity >= this->_severityLevelFilter
			);

			logging::add_common_attributes();
		}
		catch (std::exception& e)
		{
			cout << "FAILURE: " << e.what() << std::endl;
		}
	
	}

	void Logger::logInfo(string fileName, int lineNumber, string functionName, string infoMessage)
	{
		setFileNameLineAndNumber(fileName,lineNumber, functionName);
		BOOST_LOG_SEV(this->_log, info) << infoMessage;
	}

	void Logger::logDebug(string fileName, int lineNumber, string functionName, string debugMessage)
	{
		setFileNameLineAndNumber(fileName, lineNumber, functionName);
		BOOST_LOG_SEV(this->_log, debug) << debugMessage;
	}

	void Logger::logWarning(string fileName, int lineNumber, string functionName, string warningMessage)
	{
		setFileNameLineAndNumber(fileName, lineNumber, functionName);
		BOOST_LOG_SEV(this->_log, warning) << warningMessage;
	}

	void Logger::logError(string fileName, int lineNumber, string functionName, string errorMessage)
	{
		setFileNameLineAndNumber(fileName, lineNumber, functionName);
		BOOST_LOG_SEV(this->_log, error) << errorMessage;
	}

	void Logger::logFatal(string fileName, int lineNumber, string functionName, string fatalMessage)
	{
		setFileNameLineAndNumber(fileName, lineNumber, functionName);
		BOOST_LOG_SEV(this->_log, fatal) << fatalMessage;

	}

}
