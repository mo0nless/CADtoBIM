#include "../headers/TorusGraphicProperties.h"

TorusGraphicProperties::TorusGraphicProperties()
{
	this->mMinorRadius = 0;
	this->mMajorRadius = 0;
	this->mSweepRadians = 0;

	this->centerPointOfRotation = DPoint3d();
	centerPointOfRotation.x = 0;
	centerPointOfRotation.y = 0;
	centerPointOfRotation.z = 0;
}

double TorusGraphicProperties::getMinorRadius()
{
	return this->mMinorRadius;
}

void TorusGraphicProperties::setMinorRadius(double newMinorRadius)
{
	this->mMinorRadius = newMinorRadius;
}

double TorusGraphicProperties::getMajorRadius()
{
	return this->mMajorRadius;
}

void TorusGraphicProperties::setMajorRadius(double newMajorRadius)
{
	this->mMajorRadius = newMajorRadius;
}

double TorusGraphicProperties::getSweepRadians()
{
	return this->mSweepRadians;
}

void TorusGraphicProperties::setSweepRadians(double newSweepRadians)
{
	this->mSweepRadians = newSweepRadians;
}

DPoint3d TorusGraphicProperties::getCenterPointOfRotation()
{
	return this->centerPointOfRotation;
}

void TorusGraphicProperties::setCenterPointOfRotation(DPoint3d newCenterPointOfRotation)
{
	this->centerPointOfRotation = newCenterPointOfRotation;
}
