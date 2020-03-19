#include "../headers/BooleanOperationProperties.h"

BooleanOperationProperties::BooleanOperationProperties()
{
	this->booleanFunction = BooleanFunctions::BooleanFunctionsEnum::UNDEFINED;
}

BooleanFunctions::BooleanFunctionsEnum BooleanOperationProperties::getBooleanFunction()
{
	return this->booleanFunction;
}

void BooleanOperationProperties::setBooleanFunction(int newBooleanFunctionInt)
{
	this->booleanFunction = BooleanFunctions::getBooleanFunctionsEnumByIntValue(newBooleanFunctionInt);
}