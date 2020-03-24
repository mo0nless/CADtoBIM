#include "../headers/SmartFeatureGeneralProperties.h"

SmartFeatureGeneralProperties::SmartFeatureGeneralProperties()
{
	this->mLocalNodeId = -1;
	this->mLocalParentNodeId = -1;
	this->smartFeatureTypeEnum = SmartFeatureTypeEnum::SmartFeatureTypeEnum::UNDEFINED;
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
	return this->smartFeatureTypeEnum;
}

void SmartFeatureGeneralProperties::setSmartFeatureTypeEnum(SmartFeatureTypeEnum::SmartFeatureTypeEnum newSmartFeatureTypeEnum)
{
	this->smartFeatureTypeEnum = newSmartFeatureTypeEnum;;
}
