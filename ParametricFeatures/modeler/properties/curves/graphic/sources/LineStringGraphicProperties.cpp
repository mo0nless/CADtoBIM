#include "../headers//LineStringGraphicProperties.h"

LineStringGraphicProperties::LineStringGraphicProperties(): CurveGraphicProperties(CurvesPrimitivesTypeEnum::LINE_STRING)
{
}

void LineStringGraphicProperties::setDirectionTanget(DPoint3d newDirTanget)
{
	this->mDirectionTangent = newDirTanget;
}

DPoint3d LineStringGraphicProperties::getDirectionTangent()
{
	return this->mDirectionTangent;
}
