#include "../headers/CylinderGraphicProperties.h"

CylinderGraphicProperties::CylinderGraphicProperties():SolidPrimitiveProperties(PrimitiveTypeEnum::CYLINDER)
{
	this->mRadius = 0;
	this->mHeight = 0;

	this->baseOrigin = DPoint3d();
	baseOrigin.x = 0;
	baseOrigin.y = 0;
	baseOrigin.z = 0;
}

double CylinderGraphicProperties::getRadius()
{
	return this->mRadius;
}

void CylinderGraphicProperties::setRadius(double newRadius)
{
	this->mRadius = newRadius;
}

double CylinderGraphicProperties::getHeight()
{
	return this->mHeight;
}

void CylinderGraphicProperties::setHeight(double newHeight)
{
	this->mHeight = newHeight;
}

DPoint3d CylinderGraphicProperties::getBaseOrigin()
{
	return this->baseOrigin;
}

void CylinderGraphicProperties::setBaseOrigin(DPoint3d newBaseOrigin)
{
	this->baseOrigin = newBaseOrigin;
}
