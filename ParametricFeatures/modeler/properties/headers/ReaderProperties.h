#pragma once

#include<string>
#include "../../../common/properties/headers/BooleanFunctionsEnum.h"

/**
*   Class contains needed reader properties
*/
class ReaderProperties {

private:
	std::string elementDescription;
	long elementId;
	int size;
	std::string type;

	int nodeId;
	BooleanFunctions::BooleanFunctionsEnum booleanFunction;

public:
	ReaderProperties();

	int getNodeId();
	void setNodeId(int newNodeId);

	BooleanFunctions::BooleanFunctionsEnum getBooleanFunction();
	void setBooleanFunction(int newBooleanFunctionInt);

};