#include "../headers/CreateSolidsOperationProperties.h"

CreateSolidsOperationProperties::CreateSolidsOperationProperties()
{
	this->shapeProfileEnum = ShapeProfileEnum::UNDEFINED;
	this->revolveReaderProperties = nullptr;
	this->thickenReaderProperties = nullptr;
}

ShapeProfileEnum CreateSolidsOperationProperties::getShapeProfileEnum()
{
	return this->shapeProfileEnum;
}

void CreateSolidsOperationProperties::setShapeProfileEnum(ShapeProfileEnum newShapeProfileEnum)
{
	this->shapeProfileEnum = newShapeProfileEnum;
}

bool CreateSolidsOperationProperties::tryGetRevolveReaderProperties(RevolveReaderProperties& revolveReaderPropertiesR)
{
	if (this->revolveReaderProperties == nullptr) {
		return false;
	}
	revolveReaderPropertiesR = *this->revolveReaderProperties;
	return true;
}

void CreateSolidsOperationProperties::setRevolveReaderProperties(RevolveReaderProperties * newRevolveReaderProperties)
{
	this->revolveReaderProperties = newRevolveReaderProperties;
}

bool CreateSolidsOperationProperties::tryGetThickenReaderProperties(ThickenReaderProperties& thickenReaderPropertiesR)
{
	if (this->thickenReaderProperties == nullptr) {
		return false;
	}
	thickenReaderPropertiesR = *this->thickenReaderProperties;
	return true;
}

void CreateSolidsOperationProperties::setThickenReaderProperties(ThickenReaderProperties * newThickenReaderProperties)
{
	this->thickenReaderProperties = newThickenReaderProperties;
}

