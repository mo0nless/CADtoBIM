#pragma once

#include "SolidPrimitiveProperty.h"
#include "../../../curves/graphic/headers/CurvesGraphicsProperties.h"

class RotationalSweepGraphicProperties : public SolidPrimitiveProperty {

private:
	double radius;
	double sweepRadians;
	DPoint3d centerRotation;
	CurveGraphicProperties* curveGraphicProperties;

public:
	RotationalSweepGraphicProperties();


	double getRadius();
	void setRadius(double newRadius);

	double getSweepRadians();
	void setSweepRadians(double newSweepRadians);

	CurveGraphicProperties* getCurveGraphicProperties();
	void setCurveGraphicProperties(CurveGraphicProperties* newCurveGraphicProperties);

	DPoint3d getCenterRotation();
	void setCenterRotation(DPoint3d newCenterRotation);
};