#include "../headers/ReaderPropertyDefinition.h"

ReaderPropertyDefinition::ReaderPropertyDefinition(string newPropertyName, string newPropertyTypeName, ECValue newPropertyValue, string newPropertyValueAsString)
{
	this->propertyName = newPropertyName;
	this->propertyTypeName = newPropertyTypeName;
	this->propertyValue = newPropertyValue;
	this->propertyValueAsString = newPropertyValueAsString;
}

string ReaderPropertyDefinition::getPropertyName()
{
	return this->propertyName;
}

string ReaderPropertyDefinition::getPropertyTypeName()
{
	return this->propertyTypeName;
}

ECValue ReaderPropertyDefinition::getPropertyValue()
{
	return this->propertyValue;
}

string ReaderPropertyDefinition::getPropertyValueAsString()
{
	return this->propertyValueAsString;
}
