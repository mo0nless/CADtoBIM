#include "../headers/SolidPrimitiveProperty.h"

SolidPrimitiveProperty::SolidPrimitiveProperty(PrimitiveTypeEnum newPrimitiveTypeEnum)
{
	this->primitiveTypeEnum = newPrimitiveTypeEnum;
}

PrimitiveTypeEnum SolidPrimitiveProperty::getPrimitiveTypeEnum()
{
	return this->primitiveTypeEnum;
}
