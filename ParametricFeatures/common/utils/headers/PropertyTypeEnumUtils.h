#pragma once


#include<map>
#include<string>
#include "../../enums/headers/PropertyTypeEnum.h"

class PropertyTypeEnumUtils {

private:
	static const std::map<PropertyTypeEnum, std::string> mappedValues;
	PropertyTypeEnumUtils() {}

public:
	static PropertyTypeEnum getEnumByStringValue(std::string stringValue);

};