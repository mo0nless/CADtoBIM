#include "../headers/ExtrusionGraphicProperties.h"

ExtrusionGraphicProperties::ExtrusionGraphicProperties(): SolidPrimitiveProperties(PrimitiveTypeEnum::EXTRUSION)
{
	this->_shapesGraphicProperties = nullptr;
	this->_isSolid = false;
	this->_directionExtrusion = DVec3d();
}

void ExtrusionGraphicProperties::setDirectionOfExtrusion(DVec3d newDirection)
{
	this->_directionExtrusion = newDirection;
}

DVec3d ExtrusionGraphicProperties::getDirectionOfExtrusion()
{
	return this->_directionExtrusion;
}

void ExtrusionGraphicProperties::setIsSolid(bool value)
{
	this->_isSolid = value;
}

bool ExtrusionGraphicProperties::getIsSolid()
{
	return this->_isSolid;
}

double ExtrusionGraphicProperties::getLegnthOfExtrusion()
{
	return this->_directionExtrusion.Magnitude();
}

ShapesGraphicProperties * ExtrusionGraphicProperties::getShapesGraphicProperties()
{
	return this->_shapesGraphicProperties;
}

void ExtrusionGraphicProperties::setShapesGraphicProperties(ShapesGraphicProperties * newShapesGraphicProperties)
{
	this->_shapesGraphicProperties = newShapesGraphicProperties;
}

string ExtrusionGraphicProperties::toString()
{
	std::ostringstream stringStream;

	stringStream << typeid(ExtrusionGraphicProperties).name();
	if (_shapesGraphicProperties != nullptr) {
		stringStream << ", _shapesGraphicProperties = " << _shapesGraphicProperties->toString();

	}
	else {
		stringStream << ", _shapesGraphicProperties = nullptr";
	}
	stringStream << ", _isSolid = " << _isSolid;
	stringStream << ", _directionExtrusion x= " << _directionExtrusion.x << ", y= " << _directionExtrusion.y << ", z= " << _directionExtrusion.z;
	stringStream << endl;

	return stringStream.str();
}


