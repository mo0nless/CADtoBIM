#include "../headers/GraphicProperties.h"

GraphicProperties::GraphicProperties()
{
	this->mArea = 0;
	this->mVolume = 0;

	this->mCentroid = DVec3d();
	this->mCentroid.x = 0;
	this->mCentroid.y = 0;
	this->mCentroid.z = 0;

	this->mVectorAxisX = DVec3d();
	this->mVectorAxisX.x = 1;
	this->mVectorAxisX.y = 0;
	this->mVectorAxisX.z = 0;

	this->mVectorAxisY = DVec3d();
	this->mVectorAxisY.x = 0;
	this->mVectorAxisY.y = 1;
	this->mVectorAxisY.z = 0;

	this->mVectorAxisZ = DVec3d();
	this->mVectorAxisZ.x = 0;
	this->mVectorAxisZ.y = 0;
	this->mVectorAxisZ.z = 1;

	this->pCurveGraphicProperties = nullptr;
	this->pPrimitiveGraphicProperties = nullptr;
}

double GraphicProperties::getArea()
{
	return this->mArea;
}

void GraphicProperties::setArea(double newArea)
{
	this->mArea = newArea;
}

double GraphicProperties::getVolume()
{
	return this->mVolume;
}

void GraphicProperties::setVolume(double newVolume)
{
	this->mVolume = newVolume;
}

DVec3d GraphicProperties::getCentroid()
{
	return this->mCentroid;
}

void GraphicProperties::setCentroid(DVec3d newCentroid)
{
	this->mCentroid = newCentroid;
}

DVec3d GraphicProperties::getVectorAxisX()
{
	return this->mVectorAxisX;
}

void GraphicProperties::setVectorAxisX(DVec3d newVectorBaseX)
{
	this->mVectorAxisX = newVectorBaseX;
}

DVec3d GraphicProperties::getVectorAxisY()
{
	return this->mVectorAxisY;
}

void GraphicProperties::setVectorAxisY(DVec3d newVectorBaseY)
{
	this->mVectorAxisY = newVectorBaseY;
}

DVec3d GraphicProperties::getVectorAxisZ()
{
	return this->mVectorAxisZ;
}

void GraphicProperties::setVectorAxisZ(DVec3d newVectorBaseZ)
{
	this->mVectorAxisZ = newVectorBaseZ;
}

bool GraphicProperties::tryGetCurveGraphicsProperties(CurveGraphicProperties*& curveGraphicsPropertiesR)
{
	if (this->pCurveGraphicProperties == nullptr)
	{
		return false;
	}
	curveGraphicsPropertiesR = this->pCurveGraphicProperties;
	return true;
}

void GraphicProperties::setCurveGraphicsProperties(CurveGraphicProperties * newCurveGraphicsProperties)
{
	this->pCurveGraphicProperties = newCurveGraphicsProperties;
}

bool GraphicProperties::tryGetPrimitiveGraphicProperties(PrimitiveGraphicProperties*& primitiveGraphicPropertiesR)
{
	if (this->pPrimitiveGraphicProperties == nullptr)
	{
		return false;
	}
	primitiveGraphicPropertiesR = this->pPrimitiveGraphicProperties;
	return true;
}

void GraphicProperties::setPrimitiveGraphicProperties(PrimitiveGraphicProperties * newPrimitiveGraphicProperties)
{
	this->pPrimitiveGraphicProperties = newPrimitiveGraphicProperties;
}
