#include "../headers/IfcGraphicPropertiesBundle.h"

using namespace Ifc::Main;

IfcGraphicPropertiesBundle::IfcGraphicPropertiesBundle(GraphicProperties * newGraphicProperties, Ifc4::IfcGeometricRepresentationItem * newIfcRepresentationItem)
{
	this->graphicProperties = newGraphicProperties;
	this->ifcRepresentationItem = newIfcRepresentationItem;
	this->show = true;
}

IfcGraphicPropertiesBundle::IfcGraphicPropertiesBundle(ElementHandle newElementHandle, LevelHandle level)
{
	this->elementHandle = newElementHandle;
	this->_levelHandle = level;
	this->ifcRepresentationItem = nullptr;
	this->show = true;
}

void IfcGraphicPropertiesBundle::setGraphicProperties(GraphicProperties & newGraphicProperties)
{
	this->graphicProperties = &newGraphicProperties;
}

GraphicProperties * IfcGraphicPropertiesBundle::getGraphicProperties()
{
	return this->graphicProperties;
}

void IfcGraphicPropertiesBundle::setIfcRepresentationItem(Ifc4::IfcGeometricRepresentationItem * ifcRepresentationItemValue)
{
	this->ifcRepresentationItem = ifcRepresentationItemValue;
}

Ifc4::IfcGeometricRepresentationItem* IfcGraphicPropertiesBundle::getIfcRepresentationItem()
{
	return this->ifcRepresentationItem;
}

ElementHandle IfcGraphicPropertiesBundle::getElementHandle()
{
	return this->elementHandle;
}

void IfcGraphicPropertiesBundle::setElementHandle(ElementHandle newElementHandle)
{
	this->elementHandle = newElementHandle;
}

bool IfcGraphicPropertiesBundle::getShow()
{
	return this->show;
}

void IfcGraphicPropertiesBundle::setShow(bool newShow)
{
	this->show = newShow;
}

void IfcGraphicPropertiesBundle::setRepresentationTypeIdentifier(string rType, string rIdentifier)
{
	representationType = rType;
	representationIdentifier = rIdentifier;
}

string IfcGraphicPropertiesBundle::getRepresentationType()
{
	return representationType;
}

string IfcGraphicPropertiesBundle::getRepresentationIdentifier()
{
	return representationIdentifier;
}

ElemDisplayParamsCP IfcGraphicPropertiesBundle::getElemDisplayParamsCP()
{
	return this->elemDisplayParamsCP;
}

UInt32 IfcGraphicPropertiesBundle::getColor()
{
	return this->color;
}

void IfcGraphicPropertiesBundle::setColor(UInt32 newColor)
{
	this->color = newColor;
}

RgbFactor IfcGraphicPropertiesBundle::getFillColor()
{
	return fillColorDef;
}

void IfcGraphicPropertiesBundle::setFillColor(RgbFactor newColor)
{
	fillColorDef = newColor;
}

IntColorDef IfcGraphicPropertiesBundle::getLineColor()
{
	return lineColorDef;
}

void IfcGraphicPropertiesBundle::setLineColor(IntColorDef newColor)
{
	lineColorDef = newColor;
}

LevelHandle IfcGraphicPropertiesBundle::getLevelHandle()
{
	return _levelHandle;
}

void IfcGraphicPropertiesBundle::setLevelHandle(LevelHandle newlevelID)
{
	_levelHandle = newlevelID;
}

double IfcGraphicPropertiesBundle::getTransparency()
{
	return this->transparency;
}

void IfcGraphicPropertiesBundle::setTransparency(double newTransparency)
{
	this->transparency = newTransparency;
}

string IfcGraphicPropertiesBundle::getMaterial()
{
	return this->_material;
}

void IfcGraphicPropertiesBundle::setMaterial(string material)
{
	this->_material = material;
}

bool IfcGraphicPropertiesBundle::isValid()
{
	return this->ifcRepresentationItem != nullptr;
}
