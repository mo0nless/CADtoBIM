#pragma once
#include "../../enums/headers/SmartFeatureTypeEnum.h"

#include <map>
#include <string>
#include <vector>

class SmartFeatureTypeEnumUtils {
public:

	static SmartFeatureTypeEnum getSmartFeatureTypeEnumByClassName(std::string classNameValue);

private:

	SmartFeatureTypeEnumUtils() {};
	static std::map<SmartFeatureTypeEnum, std::vector<std::string>> mappedValues;
};