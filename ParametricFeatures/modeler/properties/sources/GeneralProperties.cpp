#include "../headers/GeneralProperties.h"


GeneralProperties::GeneralProperties()
{
	this->mElementClassName = std::string();
	this->mElementDescriptorName = std::string();
	this->mElementId = -1;
	this->mCurrentElementId = -1;
	this->mIsSmartFeature = false;
}

std::string GeneralProperties::getElementClassName()
{
	return this->mElementClassName;
}

void GeneralProperties::setElementClassName(std::string newClassName)
{
	this->mElementClassName = newClassName;
}

std::string GeneralProperties::getElementDescriptorName()
{
	return this->mElementDescriptorName;
}

void GeneralProperties::setElementDescriptorName(std::string newElementDescriptorName)
{
	this->mElementDescriptorName = newElementDescriptorName;
}

long GeneralProperties::getElementId()
{
	return this->mElementId;
}

void GeneralProperties::setElementId(long newElementId)
{
	this->mElementId = newElementId;
}

bool GeneralProperties::getIsSmartFeature()
{
	return this->mIsSmartFeature;
}

void GeneralProperties::setIsSmartFeature(bool newIsSmartFeature)
{
	this->mIsSmartFeature = newIsSmartFeature;
}

long GeneralProperties::getCurrentElementId()
{
	return this->mCurrentElementId;
}

void GeneralProperties::setCurrentElementId(long newCurrentElementId)
{
	this->mCurrentElementId = newCurrentElementId;
}

