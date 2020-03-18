#include "../headers/ReaderProperties.h"

ReaderProperties::ReaderProperties()
{
	this->nodeId = -1;
	this->booleanFunction = BooleanFunctions::BooleanFunctionsEnum::UNDEFINED;
}

int ReaderProperties::getNodeId()
{
	return this->nodeId;
}

void ReaderProperties::setNodeId(int newNodeId)
{
	this->nodeId = newNodeId;
}


BooleanFunctions::BooleanFunctionsEnum ReaderProperties::getBooleanFunction()
{
	return this->booleanFunction;
}

void ReaderProperties::setBooleanFunction(int newBooleanFunctionInt)
{
	this->booleanFunction = BooleanFunctions::getBooleanFunctionsEnumByIntValue(newBooleanFunctionInt);
}
