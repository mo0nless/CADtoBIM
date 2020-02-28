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

DVec3d GraphicProperties::getCentroid()
{
	return this->centroid;
}

void GraphicProperties::setCentroid(DVec3d newCentroid)
{
	this->centroid = newCentroid;
}

DVec3d GraphicProperties::getVectorBaseX()
{
	return this->vectorBaseX;
}

void GraphicProperties::setVectorBaseX(DVec3d newVectorBaseX)
{
	this->vectorBaseX = newVectorBaseX;
}

DVec3d GraphicProperties::getVectorBaseY()
{
	return this->vectorBaseY;
}

void GraphicProperties::setVectorBaseY(DVec3d newVectorBaseY)
{
	this->vectorBaseY = newVectorBaseY;
}

DVec3d GraphicProperties::getVectorBaseZ()
{
	return this->vectorBaseZ;
}

void GraphicProperties::setVectorBaseZ(DVec3d newVectorBaseZ)
{
	this->vectorBaseZ = newVectorBaseZ;
}

double GraphicProperties::getSlabLength()
{
	return this->slabLength;
}

void GraphicProperties::setSlabLength(double newSlabLength)
{
	this->slabLength = newSlabLength;
}

double GraphicProperties::getSlabWidth()
{
	return this->slabWidth;
}

void GraphicProperties::setSlabWidth(double newSlabWidth)
{
	this->slabWidth = newSlabWidth;
}

double GraphicProperties::getSlabHeight()
{
	return this->slabHeight;
}

void GraphicProperties::setSlabHeight(double newSlabHeight)
{
	this->slabHeight = newSlabHeight;
}
