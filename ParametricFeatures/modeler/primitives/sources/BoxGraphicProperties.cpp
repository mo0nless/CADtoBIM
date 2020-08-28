#include "../headers/BoxGraphicProperties.h"

BoxGraphicProperties::BoxGraphicProperties():SolidPrimitiveProperties(PrimitiveTypeEnum::BOX)
{
	this->mLength = 0;
	this->mWidth = 0;
	this->mHeight = 0;
}

double BoxGraphicProperties::getLength()
{
	return this->mLength;
}

void BoxGraphicProperties::setLength(double newLength)
{
	this->mLength = newLength;
}

double BoxGraphicProperties::getWidth()
{
	return this->mWidth;
}

void BoxGraphicProperties::setWidth(double newWidth)
{
	this->mWidth = newWidth;
}

double BoxGraphicProperties::getHeight()
{
	return this->mHeight;
}

void BoxGraphicProperties::setHeight(double newHeight)
{
	this->mHeight = newHeight;
}
