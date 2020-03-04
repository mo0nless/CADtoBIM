#include "../headers/GraphicProperties.h"

GraphicProperties::GraphicProperties()
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

	this->slabProperties = nullptr;
	this->coneProperties = nullptr;
	this->sphereProperties = nullptr;
	this->cylinderProperties = nullptr;

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

DVec3d GraphicProperties::getVectorAxisX()
{
	return this->vectorAxisX;
}

void GraphicProperties::setVectorAxisX(DVec3d newVectorBaseX)
{
	this->vectorAxisX = newVectorBaseX;
}

DVec3d GraphicProperties::getVectorAxisY()
{
	return this->vectorAxisY;
}

void GraphicProperties::setVectorAxisY(DVec3d newVectorBaseY)
{
	this->vectorAxisY = newVectorBaseY;
}

DVec3d GraphicProperties::getVectorAxisZ()
{
	return this->vectorAxisZ;
}

void GraphicProperties::setVectorAxisZ(DVec3d newVectorBaseZ)
{
	this->vectorAxisZ = newVectorBaseZ;
}

bool GraphicProperties::tryGetSlabProperties(SlabGraphicProperties& slabGraphicPropertiesR)
{

	if (this->slabProperties == nullptr) {
		return false;
	}
	slabGraphicPropertiesR = *this->slabProperties;
	return true;
}

void GraphicProperties::setSlabProperties(SlabGraphicProperties* newSlabGraphicProperties)
{
	this->slabProperties = newSlabGraphicProperties;
}

bool GraphicProperties::tryGetConeGraphicProperties(ConeGraphicProperties & coneGraphicPropertiesR)
{

	if (this->coneProperties == nullptr) {
		return false;
	}
	coneGraphicPropertiesR = *this->coneProperties;
	return true;
}

void GraphicProperties::setConeGraphicProperties(ConeGraphicProperties * newConeGraphicProperties)
{
	this->coneProperties = newConeGraphicProperties;
}

bool GraphicProperties::tryGetSphereGraphicProperties(SphereGraphicProperties & sphereGraphicPropertiesR)
{
	if (this->sphereProperties == nullptr) {
		return false;
	}
	sphereGraphicPropertiesR = *this->sphereProperties;
	return true;
}

void GraphicProperties::setSphereGraphicProperties(SphereGraphicProperties * newSphereGraphicProperties)
{
	this->sphereProperties = newSphereGraphicProperties;
}

bool GraphicProperties::tryGetCylinderGraphicProperties(CylinderGraphicProperties & cylinderGraphicPropertiesR)
{
	if (this->cylinderProperties == nullptr) {
		return false;
	}
	cylinderGraphicPropertiesR = *this->cylinderProperties;
	return true;
}

void GraphicProperties::setCylinderGraphicProperties(CylinderGraphicProperties * newCylinderGraphicProperties)
{
	this->cylinderProperties = newCylinderGraphicProperties;
}
