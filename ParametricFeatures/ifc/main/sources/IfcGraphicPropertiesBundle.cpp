#include "../headers/IfcGraphicPropertiesBundle.h"

IfcGraphicPropertiesBundle::IfcGraphicPropertiesBundle(GraphicProperties * newGraphicProperties, Ifc4::IfcGeometricRepresentationItem * newIfcRepresentationItem,
	ElementHandle newElementHandle)
{
	this->graphicProperties = newGraphicProperties;
	this->ifcRepresentationItem = newIfcRepresentationItem;
	this->elementHandle = newElementHandle;
	this->show = true;
}

IfcGraphicPropertiesBundle::IfcGraphicPropertiesBundle(GraphicProperties * newGraphicProperties, Ifc4::IfcGeometricRepresentationItem * newIfcRepresentationItem)
{
	this->graphicProperties = newGraphicProperties;
	this->ifcRepresentationItem = newIfcRepresentationItem;
	this->show = true;
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
	return  this->elementHandle;
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


