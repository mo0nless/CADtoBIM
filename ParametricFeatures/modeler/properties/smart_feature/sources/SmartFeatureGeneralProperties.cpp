#include "../headers/SmartFeatureGeneralProperties.h"

SmartFeatureGeneralProperties::SmartFeatureGeneralProperties()
{
	this->mLocalNodeId = -1;
	this->mLocalParentNodeId = -1;
	this->mSmartFeatureTypeEnum = SmartFeatureTypeEnum::SmartFeatureTypeEnum::UNDEFINED;
}

long SmartFeatureGeneralProperties::getLocalNodeId()
{
	return this->mLocalNodeId;
}

void SmartFeatureGeneralProperties::setLocalNodeId(long newLocalNodeId)
{
	this->mLocalNodeId = newLocalNodeId;
}

long SmartFeatureGeneralProperties::getLocalParentNodeId()
{
	return this->mLocalParentNodeId;
}

void SmartFeatureGeneralProperties::setLocalParentNodeId(long newLocalParentNodeId)
{
	this->mLocalParentNodeId = newLocalParentNodeId;
}

SmartFeatureTypeEnum::SmartFeatureTypeEnum SmartFeatureGeneralProperties::getSmartFeatureTypeEnum()
{
	return this->mSmartFeatureTypeEnum;
}

void SmartFeatureGeneralProperties::setSmartFeatureTypeEnum(SmartFeatureTypeEnum::SmartFeatureTypeEnum newSmartFeatureTypeEnum)
{
	this->mSmartFeatureTypeEnum = newSmartFeatureTypeEnum;;
}
