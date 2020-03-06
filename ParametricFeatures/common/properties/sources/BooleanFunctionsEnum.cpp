#include "../headers/BooleanFunctionsEnum.h"

namespace BooleanFunctions {

	BooleanFunctionsEnum getBooleanFunctionsEnumByIntValue(int value) {
		switch (value)
		{
		case static_cast<int>(BooleanFunctionsEnum::UNION) :
			return BooleanFunctionsEnum::UNION;

		case static_cast<int>(BooleanFunctionsEnum::INTERSECTION) :
			return BooleanFunctionsEnum::INTERSECTION;

		case static_cast<int>(BooleanFunctionsEnum::DIFFERENCE) :
			return BooleanFunctionsEnum::DIFFERENCE;
		case static_cast<int>(BooleanFunctionsEnum::UNDEFINED) :
			return BooleanFunctionsEnum::UNDEFINED;

		default:
			// TODO add warning log missing value
			return BooleanFunctionsEnum::UNDEFINED;
		}
	}
}