#pragma once

#include "../../stdafx.h"

//#include "boost/log/core.hpp"
//#include <boost/log/trivial.hpp>
//#include <boost/log/expressions.hpp>
//#include <boost/log/utility/setup/file.hpp>


//using namespace std;
//namespace logging = boost::log;
//namespace keywords = boost::log::keywords;

class MyLogger {

private:
	static MyLogger* _logger;


	// Private constructor so that no objects can be created.
	MyLogger();


public:
	static MyLogger *getLogger() {
		if (!_logger) {
			_logger = new MyLogger();
		}

		return _logger;
	}

};