//#pragma once
//
//#include "../../../../../common/enums/headers/PrimitiveTypeEnum.h"
//
//#include "../headers/BoxGraphicProperties.h"
//#include "../headers/ConeGraphicProperties.h"
//#include "../headers/SphereGraphicProperties.h"
//#include "../headers/CylinderGraphicProperties.h"
//#include "../headers/TorusGraphicProperties.h"
//#include "../headers/PrimitiveCommonGraphicProperties.h"
//
//
//class PrimitiveGraphicProperties {
//
//private:
//
//	PrimitiveCommonGraphicProperties* primitiveCommonGraphicProperties;
//
//	PrimitiveTypeEnum mPrimitiveTypeEnum;
//
//	BoxGraphicProperties* pSlabProperties;
//	ConeGraphicProperties* pConeProperties;
//	SphereGraphicProperties* pSphereProperties;
//	CylinderGraphicProperties* pCylinderProperties;
//	TorusGraphicProperties* pTorusProperties;
//
//public:
//	PrimitiveGraphicProperties();
//
//	PrimitiveTypeEnum getPrimitiveTypeEnum();
//	void setPrimitiveTypeEnum(PrimitiveTypeEnum newPrimitiveTypeEnum);
//
//	bool tryGetSlabProperties(BoxGraphicProperties& BoxGraphicPropertiesR);
//	void setSlabProperties(BoxGraphicProperties* newBoxGraphicProperties);
//
//	bool tryGetConeGraphicProperties(ConeGraphicProperties& coneGraphicPropertiesR);
//	void setConeGraphicProperties(ConeGraphicProperties* newConeGraphicProperties);
//
//	bool tryGetSphereGraphicProperties(SphereGraphicProperties& sphereGraphicPropertiesR);
//	void setSphereGraphicProperties(SphereGraphicProperties* newSphereGraphicProperties);
//
//	bool tryGetCylinderGraphicProperties(CylinderGraphicProperties& cylinderGraphicPropertiesR);
//	void setCylinderGraphicProperties(CylinderGraphicProperties* newCylinderGraphicProperties);
//
//	bool tryGetTorusGraphicProperties(TorusGraphicProperties& torusGraphicPropertiesR);
//	void setTorusGraphicProperties(TorusGraphicProperties* newTorusGraphicProperties);
//
//	PrimitiveCommonGraphicProperties& getPrimitiveCommonGraphicProperties();
//	void setPrimitiveCommonGraphicProperties(PrimitiveCommonGraphicProperties* newPrimitiveCommonGraphicProperties);
//
//};