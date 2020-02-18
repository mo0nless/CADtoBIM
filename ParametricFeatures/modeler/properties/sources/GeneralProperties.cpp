#include "../headers/GeneralProperties.h"


GeneralProperties::GeneralProperties()
{
	this->className = std::string();
	this->elementId = -1;
	this->currentElementId = -1;
	this->localNodeId = -1;
	this->localParentNodeId = -1;
}

std::string GeneralProperties::getClassName()
{
	return this->className;
}

void GeneralProperties::setClassName(std::string newClassName)
{
	this->className = newClassName;
}

long GeneralProperties::getElementId()
{
	return this->elementId;
}

void GeneralProperties::setElementId(long newElementId)
{
	this->elementId = newElementId;
}

long GeneralProperties::getCurrentElementId()
{
	return this->currentElementId;
}

void GeneralProperties::setCurrentElementId(long newCurrentElementId)
{
	this->currentElementId = newCurrentElementId;
}

long GeneralProperties::getLocalNodeId()
{
	return this->localNodeId;
}

void GeneralProperties::setLocalNodeId(long newLocalNodeId)
{
	this->localNodeId = newLocalNodeId;
}

long GeneralProperties::getLocalParentNodeId()
{
	return this->localParentNodeId;
}

void GeneralProperties::setLocalParentNodeId(long newLocalParentNodeId)
{
	this->localParentNodeId = newLocalParentNodeId;
}