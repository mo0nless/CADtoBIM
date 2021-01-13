#pragma once

#include "../../../../common/enums/headers/PrimitiveTypeEnum.h"
#include "../../properties/headers/GraphicProperties.h"

using namespace Common::Enums;

class SolidPrimitiveProperties : public GraphicProperties  {

private:
	PrimitiveTypeEnum primitiveTypeEnum;
public:
	SolidPrimitiveProperties(PrimitiveTypeEnum newPrimitiveTypeEnum);
	virtual ~SolidPrimitiveProperties() {}

	PrimitiveTypeEnum getPrimitiveTypeEnum();
};