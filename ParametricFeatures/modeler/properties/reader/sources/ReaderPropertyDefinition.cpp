#include "../headers/ReaderPropertyDefinition.h"

ReaderPropertyDefinition::ReaderPropertyDefinition(std::string newPropertyName, std::string newPropertyTypeName, ECValue newPropertyValue, std::string newPropertyValueAsString)
{
	this->propertyName = newPropertyName;
	this->propertyTypeName = newPropertyTypeName;
	this->propertyValue = newPropertyValue;
	this->propertyValueAsString = newPropertyValueAsString;
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

std::string ReaderPropertyDefinition::getPropertyValueAsString()
{
	return this->propertyValueAsString;
}
