#include "../headers/PropertyTypeValue.h"

PropertyTypeValue::PropertyTypeValue()
{
}

PropertyTypeValue::PropertyTypeValue(const std::string & propertyType, const boost::any & propertyValue)
{
	this->propertyType = propertyType;
	this->propertyValue = propertyValue;
}

std::string PropertyTypeValue::getPropertyType()
{
	return this->propertyType;
}

boost::any PropertyTypeValue::getPropertyValue()
{
	return this->propertyValue;
}
