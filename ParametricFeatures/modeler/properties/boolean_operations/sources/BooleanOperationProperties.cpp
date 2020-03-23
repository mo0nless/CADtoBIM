#include "../headers/BooleanOperationProperties.h"

BooleanOperationProperties::BooleanOperationProperties()
{
	this->mBooleanFunction = BooleanFunctions::BooleanFunctionsEnum::UNDEFINED;
}

BooleanFunctions::BooleanFunctionsEnum BooleanOperationProperties::getBooleanFunction()
{
	return this->mBooleanFunction;
}

void BooleanOperationProperties::setBooleanFunction(int newBooleanFunctionInt)
{
	this->mBooleanFunction = BooleanFunctions::getBooleanFunctionsEnumByIntValue(newBooleanFunctionInt);
}