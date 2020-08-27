#pragma once


#include<map>
#include<string>
#include "../../enums/headers/PropertyTypeEnum.h"

using namespace std;

class PropertyTypeEnumUtils {

private:
	static const map<PropertyTypeEnum, string> mappedValues;
	PropertyTypeEnumUtils() {}

public:
	static PropertyTypeEnum getEnumByStringValue(string stringValue);

};