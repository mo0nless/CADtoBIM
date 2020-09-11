#include "../headers/RotationalSweepGraphicProperties.h"

RotationalSweepGraphicProperties::RotationalSweepGraphicProperties() :SolidPrimitiveProperties(PrimitiveTypeEnum::ROTATIONAL_SWEEP)
{
	this->_radius=0;
	this->_sweepRadians=0;

	this->_shapesGraphicProperties = nullptr;

	this->_centerRotation = DPoint3d();
	this->_centerRotation.x = 0;
	this->_centerRotation.y = 0;
	this->_centerRotation.z = 0;
}


double RotationalSweepGraphicProperties::getRadius()
{
	return this->_radius;
}

void RotationalSweepGraphicProperties::setRadius(double newRadius)
{
	this->_radius = newRadius;
}

double RotationalSweepGraphicProperties::getSweepRadians()
{
	return this->_sweepRadians;
}

void RotationalSweepGraphicProperties::setSweepRadians(double newSweepRadians)
{
	this->_sweepRadians = newSweepRadians;
}

ShapesGraphicProperties * RotationalSweepGraphicProperties::getShapesGraphicProperties()
{
	return this->_shapesGraphicProperties;
}

void RotationalSweepGraphicProperties::setShapesGraphicProperties(ShapesGraphicProperties * newShapesGraphicProperties)
{
	this->_shapesGraphicProperties = newShapesGraphicProperties;
}

DPoint3d RotationalSweepGraphicProperties::getCenterRotation()
{
	return this->_centerRotation;
}

void RotationalSweepGraphicProperties::setCenterRotation(DPoint3d newCenterRotation)
{
	this->_centerRotation = newCenterRotation;
}

string RotationalSweepGraphicProperties::toString()
{
	std::ostringstream stringStream;

	stringStream << typeid(RotationalSweepGraphicProperties).name();
	stringStream << ", _shapesGraphicProperties = ";
	if (_shapesGraphicProperties != nullptr) {
		stringStream << _shapesGraphicProperties->toString();

	}
	else {
		stringStream << "nullptr";

	}
	stringStream << ", _radius = " << _radius;
	stringStream << ", _sweepRadians = " << _sweepRadians;
	stringStream << ", _centerRotation x= " << _centerRotation.x << ", y= " << _centerRotation.y << ", z= " << _centerRotation.z;
	stringStream << endl;

	return stringStream.str();
}

