#pragma once

#include "SolidPrimitiveProperty.h"
#include "../../../shapes/headers/ShapesGraphicProperties.h"

class RotationalSweepGraphicProperties : public SolidPrimitiveProperty {

private:
	double radius;
	double sweepRadians;
	DPoint3d centerRotation;
	ShapesGraphicProperties* shapesGraphicProperties;


public:
	RotationalSweepGraphicProperties();
	DVec3d rotationAxes, rotation;
	DRay3d axisOfRotation;
	Transform ltoW, wtoL;

	double getRadius();
	void setRadius(double newRadius);

	double getSweepRadians();
	void setSweepRadians(double newSweepRadians);

	ShapesGraphicProperties* getShapesGraphicProperties();
	void setShapesGraphicProperties(ShapesGraphicProperties* newShapesGraphicProperties);

	DPoint3d getCenterRotation();
	void setCenterRotation(DPoint3d newCenterRotation);
};