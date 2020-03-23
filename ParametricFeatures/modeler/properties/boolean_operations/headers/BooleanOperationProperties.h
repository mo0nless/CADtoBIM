#pragma once

#include "../../../../common/enums/headers/BooleanFunctionsEnum.h"

class BooleanOperationProperties {

private:
	BooleanFunctions::BooleanFunctionsEnum mBooleanFunction;

public:
	BooleanOperationProperties();

	BooleanFunctions::BooleanFunctionsEnum getBooleanFunction();
	void setBooleanFunction(int newBooleanFunctionInt);
};