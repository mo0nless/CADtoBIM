#include "../headers/GraphicProperties.h"

GraphicProperties::GraphicProperties()
{
}

double GraphicProperties::getArea()
{
	return this->area;
}

void GraphicProperties::setArea(double newArea)
{
	this->area = newArea;
}

double GraphicProperties::getVolume()
{
	return this->volume;
}

void GraphicProperties::setVolume(double newVolume)
{
	this->volume = newVolume;
}

double GraphicProperties::getRadius()
{
	return this->radius;
}

void GraphicProperties::setRadius(double newRadius)
{
	this->radius = newRadius;
}
