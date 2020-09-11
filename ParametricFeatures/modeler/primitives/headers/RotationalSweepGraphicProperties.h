#pragma once

#include "SolidPrimitiveProperties.h"
#include "../../shapes/headers/ShapesGraphicProperties.h"

class RotationalSweepGraphicProperties : public SolidPrimitiveProperties {

private:
	double _radius;
	double _sweepRadians;
	DPoint3d _centerRotation;
	ShapesGraphicProperties* _shapesGraphicProperties;


public:
	RotationalSweepGraphicProperties();
	DVec3d rotationAxes, rotation;
	DRay3d axisOfRotation;

	double getRadius();
	void setRadius(double newRadius);

	double getSweepRadians();
	void setSweepRadians(double newSweepRadians);

	ShapesGraphicProperties* getShapesGraphicProperties();
	void setShapesGraphicProperties(ShapesGraphicProperties* newShapesGraphicProperties);

	DPoint3d getCenterRotation();
	void setCenterRotation(DPoint3d newCenterRotation);

	string toString();
};