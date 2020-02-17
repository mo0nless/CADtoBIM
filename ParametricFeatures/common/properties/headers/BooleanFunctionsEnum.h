#pragma once

namespace BooleanFunctions {

	/**
	 *  Enum which defines boolean functions of the modeler and their values
	 */
	enum class BooleanFunctionsEnum {
		UNION = 1,
		INTERSECTION = 2,
		DIFFERENCE = 3,
		UNDEFINED = -1
	};

	/**
	 *  Function used to get the enum value of the boolean function by the int value from the modeler
	 *  @param value[in] boolean function value
	 *  @return BooleanFunctionsEnum
	 */
	BooleanFunctionsEnum getBooleanFunctionsEnumByIntValue(int value);

	
}