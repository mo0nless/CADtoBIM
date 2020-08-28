#include "../headers/ArcGraphicProperties.h"

ArcGraphicProperties::ArcGraphicProperties():CurveGraphicProperties(CurvesPrimitivesTypeEnum::ARC)
{
	this->mDirectionX = DVec3d();
	this->mDirectionY = DVec3d();
	this->mDirectionZ = DVec3d();

	this->mLength = 0.0;

	this->mIsCircular = false;
	this->mIsFullEllipse = false;

	this->mCenter = DVec3d();

	this->mSweepAngle = 0.0;
	this->mStartAngle = 0.0;

	this->mRadiusX = 0.0;
	this->mRadiusY = 0.0;
}

void ArcGraphicProperties::setDirectionXY(DVec3d newDirectionX, DVec3d newDirectionY)
{
	this->mDirectionX = newDirectionX;
	this->mDirectionY = newDirectionY;
	this->mDirectionZ.CrossProduct(newDirectionX, newDirectionY);
}

DVec3d ArcGraphicProperties::getDirectionX()
{
	return this->mDirectionX;
}

DVec3d ArcGraphicProperties::getDirectionY()
{
	return this->mDirectionY;
}

DVec3d ArcGraphicProperties::getDirectionZ()
{
	return this->mDirectionZ;
}

bool ArcGraphicProperties::getIsCircular()
{
	return this->mIsCircular;
}

void ArcGraphicProperties::setIsCircular(bool value)
{
	this->mIsCircular = value;
}

bool ArcGraphicProperties::getIsFullEllipse()
{
	return this->mIsFullEllipse;
}

void ArcGraphicProperties::setIsFullEllipse(bool value)
{
	this->mIsFullEllipse = value;
}

void ArcGraphicProperties::setLength(double newLength)
{
	this->mLength = newLength;
}

double ArcGraphicProperties::getLength()
{
	return this->mLength;
}

void ArcGraphicProperties::setRadiusXY(double newRadiusX, double newRadiusY)
{
	this->mRadiusX = newRadiusX;
	this->mRadiusY = newRadiusY;
}

double ArcGraphicProperties::getRadiusX()
{
	return this->mRadiusX;
}

double ArcGraphicProperties::getRadiusY()
{
	return this->mRadiusY;
}

void ArcGraphicProperties::setCenterOut(DPoint3d newCenter)
{
	this->mCenter.Init(newCenter);
}

DVec3d ArcGraphicProperties::getCenterOut()
{
	return this->mCenter;
}

void ArcGraphicProperties::setStartAngle(double newStartAngle)
{
	this->mStartAngle = newStartAngle;
}

double ArcGraphicProperties::getStartAngle()
{
	return this->mStartAngle;
}

void ArcGraphicProperties::setSweepAngle(double newSweepAngle)
{
	this->mSweepAngle = newSweepAngle;
}

double ArcGraphicProperties::getSweepAngle()
{
	return this->mSweepAngle;
}
