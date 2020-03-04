#include "../headers/SlabGraphicProperties.h"

SlabGraphicProperties::SlabGraphicProperties()
{
	this->length = 0;
	this->width = 0;
	this->height = 0;
}

double SlabGraphicProperties::getLength()
{
	return this->length;
}

void SlabGraphicProperties::setLength(double newLength)
{
	this->length = newLength;
}

double SlabGraphicProperties::getWidth()
{
	return this->width;
}

void SlabGraphicProperties::setWidth(double newWidth)
{
	this->width = newWidth;
}

double SlabGraphicProperties::getHeight()
{
	return this->height;
}

void SlabGraphicProperties::setHeight(double newHeight)
{
	this->height = newHeight;
}
