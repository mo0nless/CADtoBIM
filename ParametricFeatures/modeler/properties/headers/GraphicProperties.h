#pragma once



#include "../primitives/headers/SlabGraphicProperties.h"
#include "../primitives/headers/ConeGraphicProperties.h"
#include "../primitives/headers/SphereGraphicProperties.h"
#include "../primitives/headers/CylinderGraphicProperties.h"
#include "../primitives/headers/TorusGraphicProperties.h"

/**
 *   Class contains needed graphic properties
 */
class GraphicProperties {

private:
	double area;
	double volume;

	DVec3d centroid;

	DVec3d vectorAxisX;
	DVec3d vectorAxisY;
	DVec3d vectorAxisZ;

	SlabGraphicProperties* slabProperties;
	ConeGraphicProperties* coneProperties;
	SphereGraphicProperties* sphereProperties;
	CylinderGraphicProperties* cylinderProperties;
	TorusGraphicProperties* torusProperties;

public:
	GraphicProperties();

	double getArea();
	void setArea(double newArea);

	double getVolume();
	void setVolume(double newVolume);

	DVec3d getCentroid();
	void setCentroid(DVec3d newCentroid);

	DVec3d getVectorAxisX();
	void setVectorAxisX(DVec3d newVectorBaseX);
	
	DVec3d getVectorAxisY();
	void setVectorAxisY(DVec3d newVectorBaseY);

	DVec3d getVectorAxisZ();
	void setVectorAxisZ(DVec3d newVectorBaseZ);

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