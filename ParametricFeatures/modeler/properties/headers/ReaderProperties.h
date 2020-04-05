#pragma once

#include<string>
#include "../smart_feature/headers/SmartFeatureGeneralProperties.h"
#include "../boolean_operations/headers/BooleanOperationProperties.h"
#include "../create_solids_operations/reader/headers/CreateSolidsOperationProperties.h"
#include "../curves/reader/headers/CurveReaderProperties.h"
#include "../reader/headers/ReaderPropertyBundle.h"


/**
*   Class contains needed reader properties
*/
class ReaderProperties {

private:
	std::vector<ReaderPropertyBundle*> readerPropertyBundleVector;


	// everything down below should be removed
	int mNodeId;
	SmartFeatureGeneralProperties* pSmartFeatureGeneralProperties;

	CreateSolidsOperationProperties* pCreateSolidsOperationProperties;
	BooleanOperationProperties* pBooleanOperationProperties;
	CurveReaderProperties* pCurveReaderProperties;

public:
	ReaderProperties();

	std::vector<ReaderPropertyBundle*> getReaderPropertyBundleVector();
	void addReaderPropertyBundle(ReaderPropertyBundle* readerPropertyBundle);

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