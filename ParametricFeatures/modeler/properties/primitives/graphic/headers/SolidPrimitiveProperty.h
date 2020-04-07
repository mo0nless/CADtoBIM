#pragma once

#include "../../../../../common/enums/headers/PrimitiveTypeEnum.h"
#include "../../../headers/GraphicProperty.h"

class SolidPrimitiveProperty : public GraphicProperty  {

private:
	PrimitiveTypeEnum primitiveTypeEnum;
public:
	SolidPrimitiveProperty(PrimitiveTypeEnum newPrimitiveTypeEnum);
	virtual ~SolidPrimitiveProperty() {}

	PrimitiveTypeEnum getPrimitiveTypeEnum();
};