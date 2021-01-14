#include "../headers/SolidPrimitiveProperties.h"

using namespace Modeler::Primitives;

SolidPrimitiveProperties::SolidPrimitiveProperties(PrimitiveTypeEnum newPrimitiveTypeEnum)
{
	this->primitiveTypeEnum = newPrimitiveTypeEnum;
}

PrimitiveTypeEnum SolidPrimitiveProperties::getPrimitiveTypeEnum()
{
	return this->primitiveTypeEnum;
}
