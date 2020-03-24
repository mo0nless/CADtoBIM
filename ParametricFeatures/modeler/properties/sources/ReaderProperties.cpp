#include "../headers/ReaderProperties.h"

ReaderProperties::ReaderProperties()
{
	this->mNodeId = -1;
	this->pSmartFeatureGeneralProperties = new SmartFeatureGeneralProperties();

	this->pBooleanOperationProperties = nullptr;
	this->pCreateSolidsOperationProperties = nullptr;
}

int ReaderProperties::getNodeId()
{
	return this->mNodeId;
}

void ReaderProperties::setNodeId(int newNodeId)
{
	this->mNodeId = newNodeId;
}

SmartFeatureGeneralProperties * ReaderProperties::getSmartFeatureGeneralProperties()
{
	return this->pSmartFeatureGeneralProperties;
}

void ReaderProperties::setSmartFeatureGeneralProperties(SmartFeatureGeneralProperties * newSmartFeatureGeneralProperties)
{
	this->pSmartFeatureGeneralProperties = newSmartFeatureGeneralProperties;
}


bool ReaderProperties::tryGetCreateSolidsOperationProperties(CreateSolidsOperationProperties & createSolidsOperationPropertiesR)
{
	if (this->pCreateSolidsOperationProperties == nullptr)
	{
		return false;
	}
	createSolidsOperationPropertiesR = *this->pCreateSolidsOperationProperties;
	return true;
}

void ReaderProperties::setCreateSolidsOperationProperties(CreateSolidsOperationProperties * newCreateSolidsOperationProperties)
{
	this->pCreateSolidsOperationProperties = newCreateSolidsOperationProperties;
}

bool ReaderProperties::tryGetBooleanOperationProperties(BooleanOperationProperties & booleanOperationPropertiesR)
{
	if (this->pBooleanOperationProperties == nullptr)
	{
		return false;
	}
	booleanOperationPropertiesR = *this->pBooleanOperationProperties;
	return true;
}

void ReaderProperties::setBooleanOperationProperties(BooleanOperationProperties * newBooleanOperationProperties)
{
	this->pBooleanOperationProperties = newBooleanOperationProperties;
}

bool ReaderProperties::tryGetCurveReaderProperties(CurveReaderProperties & curveReaderPropertiesR)
{
	if (this->pCurveReaderProperties == nullptr)
	{
		return false;
	}
	curveReaderPropertiesR = *this->pCurveReaderProperties;
	return true;
}

void ReaderProperties::setCurveReaderProperties(CurveReaderProperties * newCurveReaderProperties)
{
	this->pCurveReaderProperties = newCurveReaderProperties;
}


