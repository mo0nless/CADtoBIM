#include"../headers/LineGraphicProperties.h"

LineGraphicProperties::LineGraphicProperties():CurveGraphicProperties(CurvesPrimitivesTypeEnum::LINE)
{
}

void LineGraphicProperties::setDirectionTanget(DPoint3d newDirTanget)
{
	this->mDirectionTangent = newDirTanget;
}

DPoint3d LineGraphicProperties::getDirectionTangent()
{
	return this->mDirectionTangent;
}
