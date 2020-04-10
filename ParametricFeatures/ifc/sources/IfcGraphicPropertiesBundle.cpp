#include "../headers/IfcGraphicPropertiesBundle.h"

IfcGraphicPropertiesBundle::IfcGraphicPropertiesBundle(GraphicProperties * newGraphicProperties, Ifc4::IfcRepresentationItem * newIfcRepresentationItem)
{
	this->graphicProperties = newGraphicProperties;
	this->ifcRepresentationItem = newIfcRepresentationItem;
	this->show = true;
}

GraphicProperties * IfcGraphicPropertiesBundle::getGraphicProperties()
{
	return this->graphicProperties;
}

Ifc4::IfcRepresentationItem * IfcGraphicPropertiesBundle::getIfcRepresentationItem()
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