#include "../headers/InterpolationGraphicProperties.h"


InterpolationGraphicProperties::InterpolationGraphicProperties():CurveGraphicProperties(CurvesPrimitivesTypeEnum::INTERPOLATION_CURVE)
{
	this->mDegree = 0;
	this->mOrder = 0;
	this->mIsPeriodic = false;
}

void InterpolationGraphicProperties::setOrder(size_t newOrder)
{
	this->mOrder = int(newOrder);
	this->mDegree = mOrder - 1; // A spline function of order N is a piecewise polynomial function of degree N-1 
}

int InterpolationGraphicProperties::getOrder()
{
	return this->mOrder;
}

int InterpolationGraphicProperties::getDegree()
{
	return this->mDegree;
}

void InterpolationGraphicProperties::setIsPeriodic(bool newIsPeriodic)
{
	this->mIsPeriodic = newIsPeriodic;
}

bool InterpolationGraphicProperties::getIsPeriodic()
{
	return this->mIsPeriodic;
}


