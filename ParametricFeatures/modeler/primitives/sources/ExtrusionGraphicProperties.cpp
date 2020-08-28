#include "../headers/ExtrusionGraphicProperties.h"

ExtrusionGraphicProperties::ExtrusionGraphicProperties(): SolidPrimitiveProperties(PrimitiveTypeEnum::EXTRUSION)
{
	this->mShapesGraphicProperties = nullptr;
	this->mIsSolid = false;
	this->mDirectionExtrusion = DVec3d();
}

void ExtrusionGraphicProperties::setDirectionOfExtrusion(DVec3d newDirection)
{
	this->mDirectionExtrusion = newDirection;
}

DVec3d ExtrusionGraphicProperties::getDirectionOfExtrusion()
{
	return this->mDirectionExtrusion;
}

void ExtrusionGraphicProperties::setIsSolid(bool value)
{
	this->mIsSolid = value;
}

bool ExtrusionGraphicProperties::getIsSolid()
{
	return this->mIsSolid;
}

double ExtrusionGraphicProperties::getLegnthOfExtrusion()
{
	return this->mDirectionExtrusion.Magnitude();
}

ShapesGraphicProperties * ExtrusionGraphicProperties::getShapesGraphicProperties()
{
	return this->mShapesGraphicProperties;
}

void ExtrusionGraphicProperties::setShapesGraphicProperties(ShapesGraphicProperties * newShapesGraphicProperties)
{
	this->mShapesGraphicProperties = newShapesGraphicProperties;
}


