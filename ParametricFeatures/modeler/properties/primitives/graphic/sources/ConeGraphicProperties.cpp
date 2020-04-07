#include "../headers/ConeGraphicProperties.h"

ConeGraphicProperties::ConeGraphicProperties(PrimitiveTypeEnum primitiveTypeEnum):SolidPrimitiveProperty(primitiveTypeEnum)
{
	this->mBaseRadius = 0;
	this->mTopRadius = 0;
	this->mHeight = 0;

	this->mTopOrigin = DPoint3d();
	mTopOrigin.x = 0;
	mTopOrigin.y = 0;
	mTopOrigin.z = 0;

	this->mBaseOrigin = DPoint3d();
	mBaseOrigin.x = 0;
	mBaseOrigin.y = 0;
	mBaseOrigin.z = 0;

}

double ConeGraphicProperties::getBaseRadius()
{
	return this->mBaseRadius;
}

void ConeGraphicProperties::setBaseRadius(double newBaseRadius)
{
	this->mBaseRadius = newBaseRadius;

}

double ConeGraphicProperties::getTopRadius()
{
	return this->mTopRadius;
}

void ConeGraphicProperties::setTopRadius(double newTopRadius)
{
	this->mTopRadius = newTopRadius;
}

double ConeGraphicProperties::getHeight()
{
	return this->mHeight;
}

void ConeGraphicProperties::setHeight(double newHeight)
{
	this->mHeight = newHeight;
}

DPoint3d ConeGraphicProperties::getTopOrigin()
{
	return this->mTopOrigin;
}

void ConeGraphicProperties::setTopOrigin(DPoint3d newTopOrigin)
{
	this->mTopOrigin = newTopOrigin;
}

DPoint3d ConeGraphicProperties::getBaseOrigin()
{
	return this->mBaseOrigin;
}

void ConeGraphicProperties::setBaseOrigin(DPoint3d newBaseOrigin)
{
	this->mBaseOrigin = newBaseOrigin;
}
