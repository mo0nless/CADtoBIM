#pragma once

#include "../stdafx.h"

class PropertyTypeValue {
private:
	
	std::string propertyType;
	boost::any propertyValue;
public:
	PropertyTypeValue();
	PropertyTypeValue(const std::string &propertyType, const boost::any &propertyValue);

	std::string getPropertyType();
	boost::any getPropertyValue();
};
