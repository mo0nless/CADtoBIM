#include "../headers/PointStringGraphicProperties.h"

PointStringGraphicProperties::PointStringGraphicProperties():ICurveGraphicProperties(CurvesPrimitivesTypeEnum::POINT_STRING)
{

}

bool PointStringGraphicProperties::getIsPort()
{
	return this->mIsPort;
}

void PointStringGraphicProperties::setIsPort(bool value)
{
	this->mIsPort = value;
}

