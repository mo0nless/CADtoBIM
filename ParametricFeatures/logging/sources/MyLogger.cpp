#include "..\headers\MyLogger.h"


MyLogger *MyLogger::_logger = 0;


MyLogger::MyLogger()
{
	//logging::add_file_log("sample.log");

	//logging::core::get()->set_filter
	//(
	//	logging::trivial::severity >= logging::trivial::info
	//);

	//boost::log::add_file_log
	//(
	//	boost::log::keywords::file_name = "sample_%N.log",
	//	boost::log::keywords::rotation_size = 10 * 1024 * 1024,
	//	boost::log::keywords::time_based_rotation = boost::log::sinks::file::rotation_at_time_point(0, 0, 0),
	//	boost::log::keywords::format = "[%TimeStamp%]: %Message%"
	//);

	//boost::log::core::get()->set_filter
	//(
	//	boost::log::trivial::severity >= boost::log::trivial::info
	//);
}
