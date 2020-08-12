#include "../headers/IfcGraphicPropertiesBundle.h"
#include "..\headers\IfcGraphicPropertiesBundle.h"

IfcGraphicPropertiesBundle::IfcGraphicPropertiesBundle(GraphicProperties * newGraphicProperties, Ifc4::IfcGeometricRepresentationItem * newIfcRepresentationItem,
	ElementHandle newElementHandle, ElemDisplayParamsCP newElemDisplayParamsCP)
{
	this->graphicProperties = newGraphicProperties;
	this->ifcRepresentationItem = newIfcRepresentationItem;
	this->elementHandle = newElementHandle;
	this->elemDisplayParamsCP = newElemDisplayParamsCP;
	this->show = true;

	//std::string filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
	std::string filePath = SessionManager::getInstance()->getDataOutputFilePath();
	std::ofstream outfile;
	outfile.open(filePath, std::ios_base::app);

	UInt32 color3;

	color3 = newElemDisplayParamsCP->GetLineColorTBGR();
	int blue1 = (color3 >> 16) & 0xFF;
	int green1 = (color3 >> 8) & 0xFF;
	int red1 = color3 & 0xFF;

	outfile << "IfcGraphicPropertiesBundle constructor" << std::endl;
	outfile << "RGB =" << red1 << "," << green1 << "," << blue1 << std::endl;
	outfile.close();
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

double IfcGraphicPropertiesBundle::getTransparency()
{
	return this->transparency;
}

void IfcGraphicPropertiesBundle::setTransparency(double newTransparency)
{
	this->transparency = newTransparency;
}

std::string IfcGraphicPropertiesBundle::getMaterial()
{
	return this->_material;
}

void IfcGraphicPropertiesBundle::setMaterial(std::string material)
{
	this->_material = material;
}


