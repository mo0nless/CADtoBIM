#include "../headers/ReaderProperties.h"

ReaderProperties::ReaderProperties()
{
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
