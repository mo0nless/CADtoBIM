#include "../headers/PrimitiveCommonGraphicProperties.h"

PrimitiveCommonGraphicProperties::PrimitiveCommonGraphicProperties()
{
	this->area = 0;
	this->volume = 0;

	this->centroid = DVec3d();
	this->centroid.x = 0;
	this->centroid.y = 0;
	this->centroid.z = 0;

	this->vectorAxisX = DVec3d();
	this->vectorAxisX.x = 1;
	this->vectorAxisX.y = 0;
	this->vectorAxisX.z = 0;

	this->vectorAxisY = DVec3d();
	this->vectorAxisY.x = 0;
	this->vectorAxisY.y = 1;
	this->vectorAxisY.z = 0;

	this->vectorAxisZ = DVec3d();
	this->vectorAxisZ.x = 0;
	this->vectorAxisZ.y = 0;
	this->vectorAxisZ.z = 1;
}

double PrimitiveCommonGraphicProperties::getArea()
{
	return this->area;
}

void PrimitiveCommonGraphicProperties::setArea(double newArea)
{
	this->area = newArea;
}

double PrimitiveCommonGraphicProperties::getVolume()
{
	return this->volume;
}

void PrimitiveCommonGraphicProperties::setVolume(double newVolume)
{
	this->volume = newVolume;
}

DVec3d PrimitiveCommonGraphicProperties::getCentroid()
{
	return this->centroid;
}

void PrimitiveCommonGraphicProperties::setCentroid(DVec3d newCentroid)
{
	this->centroid = newCentroid;
}

DVec3d PrimitiveCommonGraphicProperties::getVectorAxisX()
{
	return this->vectorAxisX;
}

void PrimitiveCommonGraphicProperties::setVectorAxisX(DVec3d newVectorBaseX)
{
	this->vectorAxisX = newVectorBaseX;
}

DVec3d PrimitiveCommonGraphicProperties::getVectorAxisY()
{
	return this->vectorAxisY;
}

void PrimitiveCommonGraphicProperties::setVectorAxisY(DVec3d newVectorBaseY)
{
	this->vectorAxisY = newVectorBaseY;
}

DVec3d PrimitiveCommonGraphicProperties::getVectorAxisZ()
{
	return this->vectorAxisZ;
}

void PrimitiveCommonGraphicProperties::setVectorAxisZ(DVec3d newVectorBaseZ)
{
	this->vectorAxisZ = newVectorBaseZ;
}
