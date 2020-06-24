#include "../headers/ExtrusionGraphicProperties.h"

ExtrusionGraphicProperties::ExtrusionGraphicProperties(): SolidPrimitiveProperty(PrimitiveTypeEnum::EXTRUSION)
{
	this->radius = 0;
	this->sweepRadians = 0;

	this->mShapesGraphicProperties = nullptr;

	this->centerRotation = DPoint3d();
	this->centerRotation.x = 0;
	this->centerRotation.y = 0;
	this->centerRotation.z = 0;
}

ShapesGraphicProperties * ExtrusionGraphicProperties::getShapesGraphicProperties()
{
	return this->mShapesGraphicProperties;
}

void ExtrusionGraphicProperties::setShapesGraphicProperties(ShapesGraphicProperties * newShapesGraphicProperties)
{
	this->mShapesGraphicProperties = newShapesGraphicProperties;
}


