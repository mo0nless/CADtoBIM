#include "../headers/TorusGraphicProperties.h"

TorusGraphicProperties::TorusGraphicProperties()
{
	this->mMinorRadius = 0;
	this->mMajorRadius = 0;
	this->mSweepRadians = 0;
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
