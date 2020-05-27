#include "../headers/IfcGraphicPropertiesBundle.h"
#include "..\headers\IfcGraphicPropertiesBundle.h"

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

//void IfcGraphicPropertiesBundle::setIfcRepresentationItem(Ifc4::IfcRepresentationItem * ifcRepresentationItemValue)
void IfcGraphicPropertiesBundle::setIfcRepresentationItem(Ifc4::IfcGeometricRepresentationItem * ifcRepresentationItemValue)
{
	this->ifcRepresentationItem = ifcRepresentationItemValue;
}

//Ifc4::IfcRepresentationItem * IfcGraphicPropertiesBundle::getIfcRepresentationItem()
Ifc4::IfcGeometricRepresentationItem* IfcGraphicPropertiesBundle::getIfcRepresentationItem()
{
	return this->ifcRepresentationItem;
}

bool IfcGraphicPropertiesBundle::getShow()
{
	return this->show;
}

void IfcGraphicPropertiesBundle::setShow(bool newShow)
{
	this->show = newShow;
}
