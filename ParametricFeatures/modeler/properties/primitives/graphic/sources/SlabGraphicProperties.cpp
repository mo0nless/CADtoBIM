#include "../headers/SlabGraphicProperties.h"

SlabGraphicProperties::SlabGraphicProperties()
{
	this->mLength = 0;
	this->mWidth = 0;
	this->mHeight = 0;
}

double SlabGraphicProperties::getLength()
{
	return this->mLength;
}

void SlabGraphicProperties::setLength(double newLength)
{
	this->mLength = newLength;
}

double SlabGraphicProperties::getWidth()
{
	return this->mWidth;
}

void SlabGraphicProperties::setWidth(double newWidth)
{
	this->mWidth = newWidth;
}

double SlabGraphicProperties::getHeight()
{
	return this->mHeight;
}

void SlabGraphicProperties::setHeight(double newHeight)
{
	this->mHeight = newHeight;
}
