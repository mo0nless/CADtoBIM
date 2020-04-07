#include "../headers/GraphicProperty.h"

double GraphicProperty::getArea()
{
	return this->area;
}

void GraphicProperty::setArea(double newArea)
{
	this->area = newArea;
}

double GraphicProperty::getVolume()
{
	return this->volume;
}

void GraphicProperty::setVolume(double newVolume)
{
	this->volume = newVolume;
}

DVec3d GraphicProperty::getCentroid()
{
	return this->centroid;
}

void GraphicProperty::setCentroid(DVec3d newCentroid)
{
	this->centroid = newCentroid;
}

void GraphicProperty::setVectorAxis(DVec3d newVectorAxisX, DVec3d newVectorAxisY, DVec3d newVectorAxisZ)
{
	this->vectorAxisX = newVectorAxisX;
	this->vectorAxisY = newVectorAxisY;
	this->vectorAxisZ = newVectorAxisZ;
}

DVec3d GraphicProperty::getVectorAxisX()
{
	return this->vectorAxisX;
}

DVec3d GraphicProperty::getVectorAxisY()
{
	return this->vectorAxisY;
}

DVec3d GraphicProperty::getVectorAxisZ()
{
	return this->vectorAxisZ;
}
