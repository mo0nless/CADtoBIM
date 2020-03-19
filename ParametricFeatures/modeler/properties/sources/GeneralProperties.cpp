#include "../headers/GeneralProperties.h"


GeneralProperties::GeneralProperties()
{
	this->className = std::string();
	this->elementId = -1;
	this->currentElementId = -1;
	this->isSmartFeature = false;
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

bool GeneralProperties::getIsSmartFeature()
{
	return this->isSmartFeature;
}

void GeneralProperties::setIsSmartFeature(bool newIsSmartFeature)
{
	this->isSmartFeature = newIsSmartFeature;
}

long GeneralProperties::getCurrentElementId()
{
	return this->currentElementId;
}

void GeneralProperties::setCurrentElementId(long newCurrentElementId)
{
	this->currentElementId = newCurrentElementId;
}

