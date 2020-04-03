#include "../headers/SmartFeatureGeneralProperties.h"

SmartFeatureGeneralProperties::SmartFeatureGeneralProperties()
{
	this->mLocalNodeId = -1;
	this->mLocalParentNodeId = -1;
	this->mSmartFeatureTypeEnum = SmartFeatureTypeEnum::UNDEFINED;
	this->mCreateSolidFunctionsEnum = CreateSolidFunctionsEnum::UNDEFINED;
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

SmartFeatureTypeEnum SmartFeatureGeneralProperties::getSmartFeatureTypeEnum()
{
	return this->mSmartFeatureTypeEnum;
}

CreateSolidFunctionsEnum SmartFeatureGeneralProperties::getCreateSolidTypeEnum()
{
	return this->mCreateSolidFunctionsEnum;
}

void SmartFeatureGeneralProperties::setSmartFeatureTypeEnum(SmartFeatureTypeEnum newSmartFeatureTypeEnum)
{
	this->mSmartFeatureTypeEnum = newSmartFeatureTypeEnum;
}

void SmartFeatureGeneralProperties::setSmartFeatureTypeEnum(std::string newClassName)
{
	this->mSmartFeatureTypeEnum = SmartFeatureTypeEnumUtils::getSmartFeatureTypeEnumByClassName(newClassName);
	if (mSmartFeatureTypeEnum == SmartFeatureTypeEnum::CREATE_SOLIDS)
	{
		this->mCreateSolidFunctionsEnum = CreateSolidFunctionsEnumUtils::getCreateSolidFunctionsEnumByClassName(newClassName);
	}
}
