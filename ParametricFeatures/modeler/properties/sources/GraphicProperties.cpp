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

	this->curveGraphicProperties = nullptr;
	this->primitiveGraphicProperties = nullptr;
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

bool GraphicProperties::tryGetCurveGraphicsProperties(CurveGraphicProperties*& curveGraphicsPropertiesR)
{
	if (this->curveGraphicProperties == nullptr)
	{
		return false;
	}
	curveGraphicsPropertiesR = this->curveGraphicProperties;
	return true;
}

void GraphicProperties::setCurveGraphicsProperties(CurveGraphicProperties * newCurveGraphicsProperties)
{
	this->curveGraphicProperties = newCurveGraphicsProperties;
}

bool GraphicProperties::tryGetPrimitiveGraphicProperties(PrimitiveGraphicProperties*& primitiveGraphicPropertiesR)
{
	if (this->primitiveGraphicProperties == nullptr)
	{
		return false;
	}
	primitiveGraphicPropertiesR = this->primitiveGraphicProperties;
	return true;
}

void GraphicProperties::setPrimitiveGraphicProperties(PrimitiveGraphicProperties * newPrimitiveGraphicProperties)
{
	this->primitiveGraphicProperties = newPrimitiveGraphicProperties;
}
