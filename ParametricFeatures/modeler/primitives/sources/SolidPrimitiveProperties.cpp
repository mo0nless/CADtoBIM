#include "../headers/SolidPrimitiveProperties.h"

SolidPrimitiveProperties::SolidPrimitiveProperties(PrimitiveTypeEnum newPrimitiveTypeEnum)
{
	this->primitiveTypeEnum = newPrimitiveTypeEnum;
}

PrimitiveTypeEnum SolidPrimitiveProperties::getPrimitiveTypeEnum()
{
	return this->primitiveTypeEnum;
}
