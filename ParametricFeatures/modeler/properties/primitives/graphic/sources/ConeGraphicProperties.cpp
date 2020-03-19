#include "../headers/ConeGraphicProperties.h"

ConeGraphicProperties::ConeGraphicProperties()
{
	this->baseRadius = 0;
	this->topRadius = 0;
	this->height = 0;
	this->topOrigin = DPoint3d();
	topOrigin.x = 0;
	topOrigin.y = 0;
	topOrigin.z = 0;
}

double ConeGraphicProperties::getBaseRadius()
{
	return this->baseRadius;
}

void ConeGraphicProperties::setBaseRadius(double newBaseRadius)
{
	this->baseRadius = newBaseRadius;

}

double ConeGraphicProperties::getTopRadius()
{
	return this->topRadius;
}

void ConeGraphicProperties::setTopRadius(double newTopRadius)
{
	this->topRadius = newTopRadius;
}

double ConeGraphicProperties::getHeight()
{
	return this->height;
}

void ConeGraphicProperties::setHeight(double newHeight)
{
	this->height = newHeight;
}

DPoint3d ConeGraphicProperties::getTopOrigin()
{
	return this->topOrigin;
}

void ConeGraphicProperties::setTopOrigin(DPoint3d newTopOrigin)
{
	this->topOrigin = newTopOrigin;
}

DPoint3d ConeGraphicProperties::getBaseOrigin()
{
	return this->baseOrigin;
}

void ConeGraphicProperties::setBaseOrigin(DPoint3d newBaseOrigin)
{
	this->baseOrigin = newBaseOrigin;
}
