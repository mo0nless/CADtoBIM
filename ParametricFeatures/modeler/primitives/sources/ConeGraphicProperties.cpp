#include "../headers/ConeGraphicProperties.h"

ConeGraphicProperties::ConeGraphicProperties(PrimitiveTypeEnum primitiveTypeEnum):SolidPrimitiveProperties(primitiveTypeEnum)
{

	if (primitiveTypeEnum != PrimitiveTypeEnum::CONE || primitiveTypeEnum != PrimitiveTypeEnum::TRUNCATED_CONE) {
		// throw exception and log 
	}

	this->_baseRadius = 0;
	this->_topRadius = 0;
	this->_height = 0;

	this->_topOrigin = DPoint3d();
	_topOrigin.x = 0;
	_topOrigin.y = 0;
	_topOrigin.z = 0;

	this->_baseOrigin = DPoint3d();
	_baseOrigin.x = 0;
	_baseOrigin.y = 0;
	_baseOrigin.z = 0;

}

double ConeGraphicProperties::getBaseRadius()
{
	return this->_baseRadius;
}

void ConeGraphicProperties::setBaseRadius(double newBaseRadius)
{
	this->_baseRadius = newBaseRadius;

}

double ConeGraphicProperties::getTopRadius()
{
	return this->_topRadius;
}

void ConeGraphicProperties::setTopRadius(double newTopRadius)
{
	this->_topRadius = newTopRadius;
}

double ConeGraphicProperties::getHeight()
{
	return this->_height;
}

void ConeGraphicProperties::setHeight(double newHeight)
{
	this->_height = newHeight;
}

DPoint3d ConeGraphicProperties::getTopOrigin()
{
	return this->_topOrigin;
}

void ConeGraphicProperties::setTopOrigin(DPoint3d newTopOrigin)
{
	this->_topOrigin = newTopOrigin;
}

DPoint3d ConeGraphicProperties::getBaseOrigin()
{
	return this->_baseOrigin;
}

void ConeGraphicProperties::setBaseOrigin(DPoint3d newBaseOrigin)
{
	this->_baseOrigin = newBaseOrigin;
}

string ConeGraphicProperties::toString()
{
	std::ostringstream stringStream;

	stringStream << typeid(ConeGraphicProperties).name();
	stringStream << ", _baseRadius = " << _baseRadius;
	stringStream << ", _topRadius = " << _topRadius;
	stringStream << ", _height = " << _height;
	stringStream << ", _topOrigin x= " << _topOrigin.x << ", y= "<< _topOrigin.y << ", z= "<<_topOrigin.z;
	stringStream << ", _baseOrigin x= " << _baseOrigin.x << ", y= " << _baseOrigin.y << ", z= " << _baseOrigin.z;
	stringStream << endl;

	return stringStream.str();
}
