#pragma once

#include<string>
#include "../smart_feature/headers/SmartFeatureGeneralProperties.h"
#include "../boolean_operations/headers/BooleanOperationProperties.h"
#include "../create_solids_operations/reader/headers/CreateSolidsOperationProperties.h"

/**
*   Class contains needed reader properties
*/
class ReaderProperties {

private:
	int nodeId;
	SmartFeatureGeneralProperties* smartFeatureGeneralProperties;

	CreateSolidsOperationProperties* createSolidsOperationProperties;
	BooleanOperationProperties* booleanOperationProperties;

public:
	ReaderProperties();

	int getNodeId();
	void setNodeId(int newNodeId);

	//HARD CODED FOR CURVES
	int curveDegree;

	SmartFeatureGeneralProperties* getSmartFeatureGeneralProperties();
	void setSmartFeatureGeneralProperties(SmartFeatureGeneralProperties* newSmartFeatureGeneralProperties);

	bool tryGetCreateSolidsOperationProperties(CreateSolidsOperationProperties& createSolidsOperationPropertiesR);
	void setCreateSolidsOperationProperties(CreateSolidsOperationProperties* newCreateSolidsOperationProperties);

	bool tryGetBooleanOperationProperties(BooleanOperationProperties& booleanOperationPropertiesR);
	void setBooleanOperationProperties(BooleanOperationProperties* newBooleanOperationProperties);
};