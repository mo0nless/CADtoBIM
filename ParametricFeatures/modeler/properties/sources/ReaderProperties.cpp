#include "../headers/ReaderProperties.h"

ReaderProperties::ReaderProperties()
{
	this->nodeId = -1;
	this->smartFeatureGeneralProperties = new SmartFeatureGeneralProperties();

	this->booleanOperationProperties = nullptr;
	this->createSolidsOperationProperties = nullptr;
}

int ReaderProperties::getNodeId()
{
	return this->nodeId;
}

void ReaderProperties::setNodeId(int newNodeId)
{
	this->nodeId = newNodeId;
}

SmartFeatureGeneralProperties * ReaderProperties::getSmartFeatureGeneralProperties()
{
	return this->smartFeatureGeneralProperties;
}

void ReaderProperties::setSmartFeatureGeneralProperties(SmartFeatureGeneralProperties * newSmartFeatureGeneralProperties)
{
	this->smartFeatureGeneralProperties = newSmartFeatureGeneralProperties;
}


bool ReaderProperties::tryGetCreateSolidsOperationProperties(CreateSolidsOperationProperties & createSolidsOperationPropertiesR)
{
	if (this->createSolidsOperationProperties == nullptr)
	{
		return false;
	}
	createSolidsOperationPropertiesR = *this->createSolidsOperationProperties;
	return true;
}

void ReaderProperties::setCreateSolidsOperationProperties(CreateSolidsOperationProperties * newCreateSolidsOperationProperties)
{
	this->createSolidsOperationProperties = newCreateSolidsOperationProperties;
}

bool ReaderProperties::tryGetBooleanOperationProperties(BooleanOperationProperties & booleanOperationPropertiesR)
{
	if (this->booleanOperationProperties == nullptr)
	{
		return false;
	}
	booleanOperationPropertiesR = *this->booleanOperationProperties;
	return true;
}

void ReaderProperties::setBooleanOperationProperties(BooleanOperationProperties * newBooleanOperationProperties)
{
	this->booleanOperationProperties = newBooleanOperationProperties;
}


