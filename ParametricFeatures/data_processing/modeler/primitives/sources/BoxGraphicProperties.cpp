#include "../headers/BoxGraphicProperties.h"

BoxGraphicProperties::BoxGraphicProperties():SolidPrimitiveProperties(PrimitiveTypeEnum::BOX)
{
	this->_length = 0;
	this->_width = 0;
	this->_height = 0;
}

double BoxGraphicProperties::getLength()
{
	return this->_length;
}

void BoxGraphicProperties::setLength(double newLength)
{
	this->_length = newLength;
}

double BoxGraphicProperties::getWidth()
{
	return this->_width;
}

void BoxGraphicProperties::setWidth(double newWidth)
{
	this->_width = newWidth;
}

double BoxGraphicProperties::getHeight()
{
	return this->_height;
}

void BoxGraphicProperties::setHeight(double newHeight)
{
	this->_height = newHeight;
}

string BoxGraphicProperties::toString()
{
	std::ostringstream stringStream;
	stringStream << typeid(BoxGraphicProperties).name();
	stringStream << ", _length = " << _length;
	stringStream << ", _width = " << _width;
	stringStream << ", _height = " << _height;
	stringStream << endl;
	return stringStream.str();
}
