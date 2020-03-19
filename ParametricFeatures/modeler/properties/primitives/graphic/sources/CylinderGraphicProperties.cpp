#include "../headers/CylinderGraphicProperties.h"

CylinderGraphicProperties::CylinderGraphicProperties()
{
	this->radius = 0;
	this->height = 0;
}

double CylinderGraphicProperties::getRadius()
{
	return this->radius;
}

void CylinderGraphicProperties::setRadius(double newRadius)
{
	this->radius = newRadius;
}

double CylinderGraphicProperties::getHeight()
{
	return this->height;
}

void CylinderGraphicProperties::setHeight(double newHeight)
{
	this->height = newHeight;
}
