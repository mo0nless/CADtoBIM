#include "../headers/ElementBundle.h"

ElementHandle ElementBundle::getElementHandle()
{
	return this->elementHandle;
}

void ElementBundle::setElementHandle(ElementHandle newElementHandle)
{
	this->elementHandle = newElementHandle;
}

GraphicProperties * ElementBundle::getGraphicProperties()
{
	return this->graphicProperties;
}

void ElementBundle::setGraphicProperties(GraphicProperties & newGraphicProperties)
{
	this->graphicProperties = &newGraphicProperties;
}

ReaderPropertiesBundle * ElementBundle::getReaderPropertiesBundle()
{
	return this->readerPropertiesBundle;
}

void ElementBundle::setReaderPropertiesBundle(ReaderPropertiesBundle & newReaderPropertiesBundle)
{
	this->readerPropertiesBundle = &newReaderPropertiesBundle;
}

ElemDisplayParamsCP ElementBundle::getElemDisplayParamsCP()
{
	return this->elemDisplayParamsCP;
}

void ElementBundle::setElemDisplayParamsCR(ElemDisplayParamsCR newElemDisplayParamsCR)
{
	this->elemDisplayParamsCP =  ElemDisplayParamsCP(&newElemDisplayParamsCR);

}

UInt32 ElementBundle::getColor()
{
	return this->color;
}

void ElementBundle::setColor(UInt32 newColor)
{
	this->color = newColor;
}

double ElementBundle::getTransparency()
{
	return this->transparency;
}

void ElementBundle::setTransparency(double newTransparency)
{
	this->transparency = newTransparency;
}

string ElementBundle::getMaterial()
{
	return this->_material;
}

void ElementBundle::setMaterial(string material)
{
	this->_material = material;
}
