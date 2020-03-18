#pragma once

#include<string>
#include "../../../common/enums/headers/BooleanFunctionsEnum.h"

/**
*   Class contains needed reader properties
*/
class ReaderProperties {

private:
	int nodeId;
	BooleanFunctions::BooleanFunctionsEnum booleanFunction;

public:
	ReaderProperties();

	int getNodeId();
	void setNodeId(int newNodeId);

	BooleanFunctions::BooleanFunctionsEnum getBooleanFunction();
	void setBooleanFunction(int newBooleanFunctionInt);

	//HARD CODED FOR CURVES
	int curveDegree;
};