#include "../headers/RotationalSweepGraphicProperties.h"

RotationalSweepGraphicProperties::RotationalSweepGraphicProperties() :SolidPrimitiveProperty(PrimitiveTypeEnum::ROTATIONAL_SWEEP)
{
	this->radius=0;
	this->sweepRadians=0;

	this->shapesGraphicProperties = nullptr;

	this->centerRotation = DPoint3d();
	this->centerRotation.x = 0;
	this->centerRotation.y = 0;
	this->centerRotation.z = 0;
}


double RotationalSweepGraphicProperties::getRadius()
{
	return this->radius;
}

void RotationalSweepGraphicProperties::setRadius(double newRadius)
{
	this->radius = newRadius;
}

double RotationalSweepGraphicProperties::getSweepRadians()
{
	return this->sweepRadians;
}

void RotationalSweepGraphicProperties::setSweepRadians(double newSweepRadians)
{
	this->sweepRadians = newSweepRadians;
}

ShapesGraphicProperties * RotationalSweepGraphicProperties::getShapesGraphicProperties()
{
	return this->shapesGraphicProperties;
}

void RotationalSweepGraphicProperties::setShapesGraphicProperties(ShapesGraphicProperties * newShapesGraphicProperties)
{
	this->shapesGraphicProperties = newShapesGraphicProperties;
}

DPoint3d RotationalSweepGraphicProperties::getCenterRotation()
{
	return this->centerRotation;
}

void RotationalSweepGraphicProperties::setCenterRotation(DPoint3d newCenterRotation)
{
	this->centerRotation = newCenterRotation;
}

