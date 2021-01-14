#include "../headers/GraphicProperties.h"

using namespace Modeler::Properties;
	
GraphicProperties::GraphicProperties()
{
	this->volume = 0;
	this->area = 0;

	this->centroid.x = 0;
	this->centroid.y = 0;
	this->centroid.z = 0;

	this->vectorAxisX.x = 0;
	this->vectorAxisX.y = 0;
	this->vectorAxisX.z = 0;

	this->vectorAxisY.x = 0;
	this->vectorAxisY.y = 0;
	this->vectorAxisY.z = 0;

	this->vectorAxisZ.x = 0;
	this->vectorAxisZ.y = 0;
	this->vectorAxisZ.z = 0;
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

DVec3d GraphicProperties::getCentroid()
{
	return this->centroid;
}

void GraphicProperties::setCentroid(DVec3d newCentroid)
{
	this->centroid = newCentroid;
}

DPoint3d GraphicProperties::getOrigin()
{
	return this->origin;
}

void GraphicProperties::setOrigin(DPoint3d newOrigin)
{
	this->origin = newOrigin;
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
