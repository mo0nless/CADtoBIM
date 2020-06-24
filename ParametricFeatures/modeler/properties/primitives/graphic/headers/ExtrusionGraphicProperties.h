#pragma once

#include "SolidPrimitiveProperty.h"
#include "../../../shapes/headers/ShapesGraphicProperties.h"

class ExtrusionGraphicProperties : public SolidPrimitiveProperty {

private:
	double radius;
	double sweepRadians;
	DPoint3d centerRotation;
	ShapesGraphicProperties* mShapesGraphicProperties;


public:
	ExtrusionGraphicProperties();
	DVec3d directionExtrusion;
	bool isSolid = false;

	ShapesGraphicProperties* getShapesGraphicProperties();
	void setShapesGraphicProperties(ShapesGraphicProperties* newShapesGraphicProperties);

};