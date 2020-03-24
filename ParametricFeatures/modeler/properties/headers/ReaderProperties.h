#pragma once

#include<string>
#include "../smart_feature/headers/SmartFeatureGeneralProperties.h"
#include "../boolean_operations/headers/BooleanOperationProperties.h"
#include "../create_solids_operations/reader/headers/CreateSolidsOperationProperties.h"
#include "../curves/reader/headers/CurveReaderProperties.h"

/**
*   Class contains needed reader properties
*/
class ReaderProperties {

private:
	int mNodeId;
	SmartFeatureGeneralProperties* pSmartFeatureGeneralProperties;

	CreateSolidsOperationProperties* pCreateSolidsOperationProperties;
	BooleanOperationProperties* pBooleanOperationProperties;
	CurveReaderProperties* pCurveReaderProperties;

public:
	ReaderProperties();

	int getNodeId();
	void setNodeId(int newNodeId);

	SmartFeatureGeneralProperties* getSmartFeatureGeneralProperties();
	void setSmartFeatureGeneralProperties(SmartFeatureGeneralProperties* newSmartFeatureGeneralProperties);

	bool tryGetCreateSolidsOperationProperties(CreateSolidsOperationProperties& createSolidsOperationPropertiesR);
	void setCreateSolidsOperationProperties(CreateSolidsOperationProperties* newCreateSolidsOperationProperties);

	bool tryGetBooleanOperationProperties(BooleanOperationProperties& booleanOperationPropertiesR);
	void setBooleanOperationProperties(BooleanOperationProperties* newBooleanOperationProperties);

	bool tryGetCurveReaderProperties(CurveReaderProperties& curveReaderProperties);
	void setCurveReaderProperties(CurveReaderProperties* newCurveReaderProperties);
};