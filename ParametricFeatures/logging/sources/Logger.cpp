#include "..\headers\Logger.h"

namespace Logs {


	Logger *Logger::_logger = 0;
	once_flag Logger::initInstanceFlag;
	//boost::shared_mutex Logger::_mutex;

	Logger::Logger()
	{

		try
		{
			this->_log = src::severity_logger<severity_level>();

			string logsOutputFolderPath = SessionManager::getInstance()->getCurrentDayLogsFolderPath();
			// Create a log file sink
			typedef sinks::synchronous_sink<sinks::text_file_backend > file_sink;
			boost::shared_ptr< file_sink > sink(new file_sink(
				keywords::file_name = logsOutputFolderPath+"\\file_%Y-%m-%d_%H-%M-%S.%N.log",      // file name pattern
				keywords::rotation_size = 200000,                // rotation size, in characters
				keywords::auto_flush = true
			));

			// Set up where the rotated files will be stored
			sink->locked_backend()->set_file_collector(sinks::file::make_collector(
				keywords::target = logsOutputFolderPath,                          // where to store rotated files
				keywords::max_size = 100 * 1024 * 1024,              // maximum total size of the stored files, in bytes
				keywords::min_free_space = 1000 * 1024 * 1024        // minimum free space on the drive, in bytes
			));

			// Upon restart, scan the target directory for files matching the file_name pattern
			sink->locked_backend()->scan_for_files();


			sink->set_formatter
			(
				expr::format("%1%: [%2%]: <%3%> [%4% : %5% : %6% : %7%] - %8%")
				% expr::attr<unsigned int>("RecordID")
				% expr::attr<boost::posix_time::ptime>("TimeStamp")
				% severity
				% expr::attr<string>("Thread")
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
			
			logging::core::get()->add_global_attribute("Thread", shared_mc<string>(""));
			logging::core::get()->add_global_attribute("File", shared_mc<string>(""));
			logging::core::get()->add_global_attribute("Line", shared_mc<int>(0));
			logging::core::get()->add_global_attribute("Function", shared_mc<string>(""));

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
		BOOST_LOG_SEV(this->_log, error) << "! ERROR ! - " + errorMessage;
	}

	void Logger::logError(string fileName, int lineNumber, string functionName, exception & ex, string errorMessage)
	{
		string msg = "- Exception message = " + string(ex.what()) + "--" + errorMessage;
		getLogger()->logError(fileName, lineNumber, functionName, msg);
	}

	void Logger::logFatal(string fileName, int lineNumber, string functionName, string fatalMessage)
	{
		setFileNameLineAndNumber(fileName, lineNumber, functionName);
		BOOST_LOG_SEV(this->_log, fatal) << "! FATAL ERROR ! - " + fatalMessage;
	}

	void Logger::logFatal(string fileName, int lineNumber, string functionName, exception & ex, string fatalMessage)
	{
		string msg = "- Exception message = " + string(ex.what()) + "--" + fatalMessage;
		getLogger()->logError(fileName, lineNumber, functionName, msg);
	}

}
