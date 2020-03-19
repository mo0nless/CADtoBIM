#pragma once

#include "../primitives/graphic/headers/PrimitiveGraphicProperties.h"
#include "../curves/graphic/headers/CurveGraphicProperties.h"

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

	PrimitiveGraphicProperties* primitiveGraphicProperties;
	CurveGraphicProperties* curveGraphicProperties;

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

	bool tryGetCurveGraphicsProperties(CurveGraphicProperties*& curveGraphicsPropertiesR);
	void setCurveGraphicsProperties(CurveGraphicProperties* newCurveGraphicsProperties);

	bool tryGetPrimitiveGraphicProperties(PrimitiveGraphicProperties*& primitiveGraphicPropertiesR);
	void setPrimitiveGraphicProperties(PrimitiveGraphicProperties* newPrimitiveGraphicProperties);
};