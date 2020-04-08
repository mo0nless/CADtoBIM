#include"../headers/LineGraphicProperties.h"

LineGraphicProperties::LineGraphicProperties():ICurveGraphicProperties(CurvesPrimitivesTypeEnum::LINE)
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
