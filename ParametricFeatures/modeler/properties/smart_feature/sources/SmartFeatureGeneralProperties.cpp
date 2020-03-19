#include "../headers/SmartFeatureGeneralProperties.h"

SmartFeatureGeneralProperties::SmartFeatureGeneralProperties()
{
	this->localNodeId = -1;
	this->localParentNodeId = -1;
	this->smartFeatureTypeEnum = SmartFeatureTypeEnum::SmartFeatureTypeEnum::UNDEFINED;
}

long SmartFeatureGeneralProperties::getLocalNodeId()
{
	return this->localNodeId;
}

void SmartFeatureGeneralProperties::setLocalNodeId(long newLocalNodeId)
{
	this->localNodeId = newLocalNodeId;
}

long SmartFeatureGeneralProperties::getLocalParentNodeId()
{
	return this->localParentNodeId;
}

void SmartFeatureGeneralProperties::setLocalParentNodeId(long newLocalParentNodeId)
{
	this->localParentNodeId = newLocalParentNodeId;
}

SmartFeatureTypeEnum::SmartFeatureTypeEnum SmartFeatureGeneralProperties::getSmartFeatureTypeEnum()
{
	return this->smartFeatureTypeEnum;
}

void SmartFeatureGeneralProperties::setSmartFeatureTypeEnum(SmartFeatureTypeEnum::SmartFeatureTypeEnum newSmartFeatureTypeEnum)
{
	this->smartFeatureTypeEnum = newSmartFeatureTypeEnum;;
}
