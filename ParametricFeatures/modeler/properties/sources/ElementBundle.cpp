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

vector<ReaderPropertiesBundle*> ElementBundle::getReaderPropertiesBundleVector()
{
	return this->readerPropertiesBundleVector;
}

void ElementBundle::addReaderPropertiesBundle(ReaderPropertiesBundle * newReaderPropertiesBundle)
{
	this->readerPropertiesBundleVector.push_back(newReaderPropertiesBundle);
}

void ElementBundle::setReaderPropertiesBundle(vector<ReaderPropertiesBundle*> newReaderPropertiesBundleVector)
{
	this->readerPropertiesBundleVector = newReaderPropertiesBundleVector;
}

UInt32 ElementBundle::getColor()
{
	return this->_color;
}

void ElementBundle::setColor(UInt32 newColor)
{
	this->_color = newColor;
}

double ElementBundle::getTransparency()
{
	return this->_transparency;
}

void ElementBundle::setTransparency(double newTransparency)
{
	this->_transparency = newTransparency;
}

string ElementBundle::getMaterial()
{
	return this->_material;
}

void ElementBundle::setMaterial(string material)
{
	this->_material = material;
}

string ElementBundle::toString()
{
	std::ostringstream stringStream;

	stringStream << typeid(ElementBundle).name();
	stringStream << ", color = " << _color;
	stringStream << ", transparency = " << _transparency;
	stringStream << ", _material = " << _material;
	stringStream << endl;

	return stringStream.str();
}
