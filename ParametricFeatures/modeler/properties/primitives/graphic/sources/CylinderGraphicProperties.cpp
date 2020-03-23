#include "../headers/CylinderGraphicProperties.h"

CylinderGraphicProperties::CylinderGraphicProperties()
{
	this->mRadius = 0;
	this->mHeight = 0;
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
