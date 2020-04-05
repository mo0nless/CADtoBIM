#include "../headers/ReaderPropertyDefinition.h"

ReaderPropertyDefinition::ReaderPropertyDefinition(std::string newPropertyName, std::string newPropertyTypeName, ECValue newPropertyValue)
{
	this->propertyName = newPropertyName;
	this->propertyTypeName = newPropertyTypeName;
	this->propertyValue = newPropertyValue;
}

std::string ReaderPropertyDefinition::getPropertyName()
{
	return this->propertyName;
}

std::string ReaderPropertyDefinition::getPropertyTypeName()
{
	return this->propertyTypeName;
}

ECValue ReaderPropertyDefinition::getPropertyValue()
{
	return this->propertyValue;
}
