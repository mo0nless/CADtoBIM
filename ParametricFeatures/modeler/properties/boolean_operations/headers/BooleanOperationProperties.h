#pragma once

#include "../../../../common/enums/headers/BooleanFunctionsEnum.h"

class BooleanOperationProperties {

private:
	BooleanFunctions::BooleanFunctionsEnum booleanFunction;

public:
	BooleanOperationProperties();

	BooleanFunctions::BooleanFunctionsEnum getBooleanFunction();
	void setBooleanFunction(int newBooleanFunctionInt);
};