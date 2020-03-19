#pragma once

#include "../../../../../common/enums/headers/PrimitiveTypeEnum.h"

#include "../headers/SlabGraphicProperties.h"
#include "../headers/ConeGraphicProperties.h"
#include "../headers/SphereGraphicProperties.h"
#include "../headers/CylinderGraphicProperties.h"
#include "../headers/TorusGraphicProperties.h"


class PrimitiveGraphicProperties {

private:
	PrimitiveTypeEnum::PrimitiveTypeEnum primitiveTypeEnum;

	SlabGraphicProperties* slabProperties;
	ConeGraphicProperties* coneProperties;
	SphereGraphicProperties* sphereProperties;
	CylinderGraphicProperties* cylinderProperties;
	TorusGraphicProperties* torusProperties;

public:
	PrimitiveGraphicProperties();

	PrimitiveTypeEnum::PrimitiveTypeEnum getPrimitiveTypeEnum();
	void setPrimitiveTypeEnum(PrimitiveTypeEnum::PrimitiveTypeEnum newPrimitiveTypeEnum);

	bool tryGetSlabProperties(SlabGraphicProperties& slabGraphicPropertiesR);
	void setSlabProperties(SlabGraphicProperties* newSlabGraphicProperties);

	bool tryGetConeGraphicProperties(ConeGraphicProperties& coneGraphicPropertiesR);
	void setConeGraphicProperties(ConeGraphicProperties* newConeGraphicProperties);

	bool tryGetSphereGraphicProperties(SphereGraphicProperties& sphereGraphicPropertiesR);
	void setSphereGraphicProperties(SphereGraphicProperties* newSphereGraphicProperties);

	bool tryGetCylinderGraphicProperties(CylinderGraphicProperties& cylinderGraphicPropertiesR);
	void setCylinderGraphicProperties(CylinderGraphicProperties* newCylinderGraphicProperties);

	bool tryGetTorusGraphicProperties(TorusGraphicProperties& torusGraphicPropertiesR);
	void setTorusGraphicProperties(TorusGraphicProperties* newTorusGraphicProperties);


};