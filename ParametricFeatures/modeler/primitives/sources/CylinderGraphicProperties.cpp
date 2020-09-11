#include "../headers/CylinderGraphicProperties.h"

CylinderGraphicProperties::CylinderGraphicProperties():SolidPrimitiveProperties(PrimitiveTypeEnum::CYLINDER)
{
	this->_radius = 0;
	this->_height = 0;

	this->_baseOrigin = DPoint3d();
	_baseOrigin.x = 0;
	_baseOrigin.y = 0;
	_baseOrigin.z = 0;
}

double CylinderGraphicProperties::getRadius()
{
	return this->_radius;
}

void CylinderGraphicProperties::setRadius(double newRadius)
{
	this->_radius = newRadius;
}

double CylinderGraphicProperties::getHeight()
{
	return this->_height;
}

void CylinderGraphicProperties::setHeight(double newHeight)
{
	this->_height = newHeight;
}

DPoint3d CylinderGraphicProperties::getBaseOrigin()
{
	return this->_baseOrigin;
}

void CylinderGraphicProperties::setBaseOrigin(DPoint3d newBaseOrigin)
{
	this->_baseOrigin = newBaseOrigin;
}

string CylinderGraphicProperties::toString()
{
	std::ostringstream stringStream;

	stringStream << typeid(CylinderGraphicProperties).name();
	stringStream << ", _radius = " << _radius;
	stringStream << ", _height = " << _height;
	stringStream << ", _baseOrigin x= " << _baseOrigin.x << ", y= " << _baseOrigin.y << ", z= " << _baseOrigin.z;
	stringStream << endl;

	return stringStream.str();
}
