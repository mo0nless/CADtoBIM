#pragma once

#include "RevolveReaderProperties.h"
#include "ThickenReaderProperties.h"
#include "../../../../../common/enums/headers/ShapeProfileEnum.h"

class CreateSolidsOperationProperties {

private:
	ShapeProfileEnum shapeProfileEnum;

	RevolveReaderProperties* revolveReaderProperties;
	ThickenReaderProperties* thickenReaderProperties;

public:
	CreateSolidsOperationProperties();

	ShapeProfileEnum getShapeProfileEnum();
	void setShapeProfileEnum(ShapeProfileEnum newShapeProfileEnum);

	bool tryGetRevolveReaderProperties(RevolveReaderProperties& revolveReaderPropertiesR);
	void setRevolveReaderProperties(RevolveReaderProperties* newRevolveReaderProperties);

	bool tryGetThickenReaderProperties(ThickenReaderProperties& thickenReaderPropertiesR);
	void setThickenReaderProperties(ThickenReaderProperties* newThickenReaderProperties);

};