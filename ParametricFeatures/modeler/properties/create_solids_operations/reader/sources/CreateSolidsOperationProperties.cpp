#include "../headers/CreateSolidsOperationProperties.h"

CreateSolidsOperationProperties::CreateSolidsOperationProperties()
{
	this->mCreateSolidFunctionsEnum = CreateSolidFunctionsEnum::UNDEFINED;
	this->revolveReaderProperties = nullptr;
	this->extrusionReaderProperties = nullptr;
}

CreateSolidFunctionsEnum CreateSolidsOperationProperties::getCreateSolidTypeEnum()
{
	return this->mCreateSolidFunctionsEnum;
}

void CreateSolidsOperationProperties::setCreateSolidTypeEnum(CreateSolidFunctionsEnum value)
{
	this->mCreateSolidFunctionsEnum = value;
}

bool CreateSolidsOperationProperties::tryGetRevolveReaderProperties(RevolveReaderProperties*& revolveReaderPropertiesR)
{
	if (this->revolveReaderProperties == nullptr) {
		return false;
	}
	revolveReaderPropertiesR = this->revolveReaderProperties;
	return true;
}

void CreateSolidsOperationProperties::setRevolveReaderProperties(RevolveReaderProperties * newRevolveReaderProperties)
{
	this->revolveReaderProperties = newRevolveReaderProperties;
}

bool CreateSolidsOperationProperties::tryGetExtrusionReaderProperties(ExtrusionReaderProperties*& extrusionReaderPropertiesR)
{
	if (this->extrusionReaderProperties == nullptr) {
		return false;
	}
	extrusionReaderPropertiesR = this->extrusionReaderProperties;
	return true;
}

void CreateSolidsOperationProperties::setExtrusionReaderProperties(ExtrusionReaderProperties * newThickenReaderProperties)
{
	this->extrusionReaderProperties = newThickenReaderProperties;
}

