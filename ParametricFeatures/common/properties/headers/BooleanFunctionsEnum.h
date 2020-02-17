#pragma once

namespace BooleanFunctions {

	enum class BooleanFunctionsEnum {
		UNION = 1,
		INTERSECTION = 2,
		DIFFERENCE = 3,
		UNDEFINED = -1
	};

	BooleanFunctionsEnum getBooleanFunctionsEnumByIntValue(int value);

	
}