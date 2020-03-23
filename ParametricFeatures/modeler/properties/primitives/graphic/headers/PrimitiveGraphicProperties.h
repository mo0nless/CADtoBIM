#pragma once

#include "../../../../../common/enums/headers/PrimitiveTypeEnum.h"

#include "../headers/SlabGraphicProperties.h"
#include "../headers/ConeGraphicProperties.h"
#include "../headers/SphereGraphicProperties.h"
#include "../headers/CylinderGraphicProperties.h"
#include "../headers/TorusGraphicProperties.h"


class PrimitiveGraphicProperties {

private:
	PrimitiveTypeEnum mPrimitiveTypeEnum;

	SlabGraphicProperties* mSlabProperties;
	ConeGraphicProperties* mConeProperties;
	SphereGraphicProperties* mSphereProperties;
	CylinderGraphicProperties* mCylinderProperties;
	TorusGraphicProperties* mTorusProperties;

public:
	PrimitiveGraphicProperties();

	PrimitiveTypeEnum getPrimitiveTypeEnum();
	void setPrimitiveTypeEnum(PrimitiveTypeEnum newPrimitiveTypeEnum);

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