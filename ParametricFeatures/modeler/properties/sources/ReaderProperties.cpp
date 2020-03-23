#include "../headers/ReaderProperties.h"

ReaderProperties::ReaderProperties()
{
	this->mNodeId = -1;
	this->mSmartFeatureGeneralProperties = new SmartFeatureGeneralProperties();

	this->mBooleanOperationProperties = nullptr;
	this->mCreateSolidsOperationProperties = nullptr;
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
	return this->mSmartFeatureGeneralProperties;
}

void ReaderProperties::setSmartFeatureGeneralProperties(SmartFeatureGeneralProperties * newSmartFeatureGeneralProperties)
{
	this->mSmartFeatureGeneralProperties = newSmartFeatureGeneralProperties;
}


bool ReaderProperties::tryGetCreateSolidsOperationProperties(CreateSolidsOperationProperties & createSolidsOperationPropertiesR)
{
	if (this->mCreateSolidsOperationProperties == nullptr)
	{
		return false;
	}
	createSolidsOperationPropertiesR = *this->mCreateSolidsOperationProperties;
	return true;
}

void ReaderProperties::setCreateSolidsOperationProperties(CreateSolidsOperationProperties * newCreateSolidsOperationProperties)
{
	this->mCreateSolidsOperationProperties = newCreateSolidsOperationProperties;
}

bool ReaderProperties::tryGetBooleanOperationProperties(BooleanOperationProperties & booleanOperationPropertiesR)
{
	if (this->mBooleanOperationProperties == nullptr)
	{
		return false;
	}
	booleanOperationPropertiesR = *this->mBooleanOperationProperties;
	return true;
}

void ReaderProperties::setBooleanOperationProperties(BooleanOperationProperties * newBooleanOperationProperties)
{
	this->mBooleanOperationProperties = newBooleanOperationProperties;
}


