#include"../headers/LineGraphicProperties.h"

LineGraphicProperties::LineGraphicProperties()
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
