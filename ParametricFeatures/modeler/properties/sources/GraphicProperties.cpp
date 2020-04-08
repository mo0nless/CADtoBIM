#include "../headers/GraphicProperties.h"

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

DVec3d GraphicProperties::getCentroid()
{
	return this->centroid;
}

void GraphicProperties::setCentroid(DVec3d newCentroid)
{
	this->centroid = newCentroid;
}

void GraphicProperties::setVectorAxis(DVec3d newVectorAxisX, DVec3d newVectorAxisY, DVec3d newVectorAxisZ)
{
	this->vectorAxisX = newVectorAxisX;
	this->vectorAxisY = newVectorAxisY;
	this->vectorAxisZ = newVectorAxisZ;
}

DVec3d GraphicProperties::getVectorAxisX()
{
	return this->vectorAxisX;
}

DVec3d GraphicProperties::getVectorAxisY()
{
	return this->vectorAxisY;
}

DVec3d GraphicProperties::getVectorAxisZ()
{
	return this->vectorAxisZ;
}
