#include "../headers/GraphicGeomBundle.h"

ElementHandle GraphicGeomBundle::getElementHandle()
{
	return this->elementHandle;
}

void GraphicGeomBundle::setElementHandle(ElementHandle newElementHandle)
{
	this->elementHandle = newElementHandle;
}

GraphicProperties * GraphicGeomBundle::getGraphicProperties()
{
	return this->graphicProperties;
}

void GraphicGeomBundle::setGraphicProperties(GraphicProperties & newGraphicProperties)
{
	this->graphicProperties = &newGraphicProperties;
}

vector<ReaderPropertiesBundle*> GraphicGeomBundle::getReaderPropertiesBundleVector()
{
	return this->readerPropertiesBundleVector;
}

void GraphicGeomBundle::addReaderPropertiesBundle(ReaderPropertiesBundle * newReaderPropertiesBundle)
{
	this->readerPropertiesBundleVector.push_back(newReaderPropertiesBundle);
}

void GraphicGeomBundle::setReaderPropertiesBundle(vector<ReaderPropertiesBundle*> newReaderPropertiesBundleVector)
{
	this->readerPropertiesBundleVector = newReaderPropertiesBundleVector;
}

UInt32 GraphicGeomBundle::getColor()
{
	return this->_color;
}

void GraphicGeomBundle::setColor(UInt32 newColor)
{
	this->_color = newColor;
}

LevelHandle GraphicGeomBundle::getLevelHandle()
{
	return _levelID;
}

void GraphicGeomBundle::setLevelHandle(LevelHandle level)
{
	this->_levelID = level;
}

double GraphicGeomBundle::getTransparency()
{
	return this->_transparency;
}

void GraphicGeomBundle::setTransparency(double newTransparency)
{
	this->_transparency = newTransparency;
}

string GraphicGeomBundle::getMaterial()
{
	return this->_material;
}

void GraphicGeomBundle::setMaterial(string material)
{
	this->_material = material;
}

string GraphicGeomBundle::toString()
{
	std::ostringstream stringStream;

	stringStream << typeid(GraphicGeomBundle).name();
	stringStream << ", color = " << _color;
	stringStream << ", transparency = " << _transparency;
	stringStream << ", _material = " << _material;
	stringStream << endl;

	return stringStream.str();
}
