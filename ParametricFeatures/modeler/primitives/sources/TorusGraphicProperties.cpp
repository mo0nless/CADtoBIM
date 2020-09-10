#include "../headers/TorusGraphicProperties.h"

TorusGraphicProperties::TorusGraphicProperties():SolidPrimitiveProperties(PrimitiveTypeEnum::TORUS)
{
	this->_minorRadius = 0;
	this->_majorRadius = 0;
	this->_sweepRadians = 0;

	this->_centerPointOfRotation = DPoint3d();
	_centerPointOfRotation.x = 0;
	_centerPointOfRotation.y = 0;
	_centerPointOfRotation.z = 0;
}

double TorusGraphicProperties::getMinorRadius()
{
	return this->_minorRadius;
}

void TorusGraphicProperties::setMinorRadius(double newMinorRadius)
{
	this->_minorRadius = newMinorRadius;
}

double TorusGraphicProperties::getMajorRadius()
{
	return this->_majorRadius;
}

void TorusGraphicProperties::setMajorRadius(double newMajorRadius)
{
	this->_majorRadius = newMajorRadius;
}

double TorusGraphicProperties::getSweepRadians()
{
	return this->_sweepRadians;
}

void TorusGraphicProperties::setSweepRadians(double newSweepRadians)
{
	this->_sweepRadians = newSweepRadians;
}

DPoint3d TorusGraphicProperties::getCenterPointOfRotation()
{
	return this->_centerPointOfRotation;
}

void TorusGraphicProperties::setCenterPointOfRotation(DPoint3d newCenterPointOfRotation)
{
	this->_centerPointOfRotation = newCenterPointOfRotation;
}

string TorusGraphicProperties::toString()
{
	std::ostringstream stringStream;

	stringStream << typeid(TorusGraphicProperties).name();
	stringStream << ", _minorRadius = " << _minorRadius;
	stringStream << ", _majorRadius = " << _majorRadius;
	stringStream << ", _sweepRadians = " << _sweepRadians;
	stringStream << ", _centerPointOfRotation x= " << _centerPointOfRotation.x << ", y= " << _centerPointOfRotation.y << ", z= " << _centerPointOfRotation.z;
	stringStream << endl;

	return stringStream.str();
}
