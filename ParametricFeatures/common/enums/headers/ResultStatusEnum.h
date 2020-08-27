#pragma once

#include <string>
#include <map>

using namespace std;

namespace ResultStatusEnum {
	/**
	*  Result status values of the execution
	*/
	enum class ResultStatusEnum {
		SUCCESS = 0,
		NO_RESULT = 1,
		ERROR = 2
	};
}
