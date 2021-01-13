#include"../headers/LineGraphicProperties.h"

LineGraphicProperties::LineGraphicProperties():CurveGraphicProperties(CurvesPrimitivesTypeEnum::LINE)
{
}

void LineGraphicProperties::setDirectionTanget(DVec3d newDirTanget)
{
	this->mDirectionTangent = newDirTanget;
}

DVec3d LineGraphicProperties::getDirectionTangent()
{
	return this->mDirectionTangent;
}
