#include "../headers/SmartFeatureProperties.h"

SmartFeatureProperties::SmartFeatureProperties()
{
	this->graphicProperties = new GraphicProperties();
	this->readerProperties = new ReaderProperties();
	this->className =  std::string();
	this->elementId = -1;
	this->currentElementId = -1;
	this->localNodeId = -1;
	this->localParentNodeId = -1;
}

std::string SmartFeatureProperties::getClassName()
{
	return this->className;
}

void SmartFeatureProperties::setClassName(std::string newClassName)
{
	this->className = newClassName;
}

long SmartFeatureProperties::getElementId()
{
	return this->elementId;
}

void SmartFeatureProperties::setElementId(long newElementId)
{
	this->elementId = newElementId;
}

long SmartFeatureProperties::getCurrentElementId()
{
	return this->currentElementId;
}

void SmartFeatureProperties::setCurrentElementId(long newCurrentElementId)
{
	this->currentElementId = newCurrentElementId;
}

long SmartFeatureProperties::getLocalNodeId()
{
	return this->localNodeId;
}

void SmartFeatureProperties::setLocalNodeId(long newLocalNodeId)
{
	this->localNodeId = newLocalNodeId;
}

long SmartFeatureProperties::getLocalParentNodeId()
{
	return this->localParentNodeId;
}

void SmartFeatureProperties::setLocalParentNodeId(long newLocalParentNodeId)
{
	this->localParentNodeId = newLocalParentNodeId;
}

ReaderProperties* SmartFeatureProperties::getReaderProperties()
{
	return this->readerProperties;
}

void SmartFeatureProperties::setReaderProperties(ReaderProperties* newReaderProperties)
{
	this->readerProperties = newReaderProperties;
}

GraphicProperties* SmartFeatureProperties::getGraphicProperties()
{
	return this->graphicProperties;
}

void SmartFeatureProperties::setGraphicProperties(GraphicProperties* newGraphicProperties)
{
	this->graphicProperties = newGraphicProperties;
}
