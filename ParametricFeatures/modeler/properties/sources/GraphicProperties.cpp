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

RotMatrix GraphicProperties::getRotMatrixAxis()
{
	return this->rotMatrix;
}

void GraphicProperties::setRotMatrixAxis(RotMatrix rotationMatrix)
{
	this->rotMatrix = rotationMatrix;
}

DVec3d GraphicProperties::getMomentxyz()
{
	return this->momentxyz;
}

void GraphicProperties::setMomentxyz(DVec3d newMomentxyz)
{
	this->momentxyz = newMomentxyz;
}
