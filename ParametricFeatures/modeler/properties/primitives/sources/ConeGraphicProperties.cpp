#include "../headers/ConeGraphicProperties.h"

ConeGraphicProperties::ConeGraphicProperties()
{
	this->baseRadius = 0;
	this->topRadius = 0;
	this->height = 0;
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
