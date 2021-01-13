#include "../headers/SphereGraphicProperties.h"

SphereGraphicProperties::SphereGraphicProperties():SolidPrimitiveProperties(PrimitiveTypeEnum::SPHERE)
{
	this->_radius = 0;
}

double SphereGraphicProperties::getRadius()
{
	return this->_radius;
}

void SphereGraphicProperties::setRadius(double newRadius)
{
	this->_radius = newRadius;
}

string SphereGraphicProperties::toString()
{
	std::ostringstream stringStream;

	stringStream << typeid(SphereGraphicProperties).name();
	stringStream << ", _radius = " << _radius;
	stringStream << endl;

	return stringStream.str();
}
