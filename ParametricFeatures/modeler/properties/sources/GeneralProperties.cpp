#include "../headers/GeneralProperties.h"


GeneralProperties::GeneralProperties()
{
	this->mElementClassName = string();
	this->mElementDescriptorName = string();
	this->mElementId = -1;
	this->mCurrentElementId = -1;
	this->mIsSmartFeature = false;
}

string GeneralProperties::getElementClassName()
{
	return this->mElementClassName;
}

void GeneralProperties::setElementClassName(string newClassName)
{
	this->mElementClassName = newClassName;
}

string GeneralProperties::getElementDescriptorName()
{
	return this->mElementDescriptorName;
}

void GeneralProperties::setElementDescriptorName(string newElementDescriptorName)
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

string GeneralProperties::toString()
{
	return string();
}

