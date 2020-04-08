#pragma once

#include "../../../../../common/enums/headers/PrimitiveTypeEnum.h"
#include "../../../headers/GraphicProperties.h"

class SolidPrimitiveProperty : public GraphicProperties  {

private:
	PrimitiveTypeEnum primitiveTypeEnum;
public:
	SolidPrimitiveProperty(PrimitiveTypeEnum newPrimitiveTypeEnum);
	virtual ~SolidPrimitiveProperty() {}

	PrimitiveTypeEnum getPrimitiveTypeEnum();
};