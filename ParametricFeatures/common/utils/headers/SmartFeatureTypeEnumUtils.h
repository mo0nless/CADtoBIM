#pragma once
#include "../../enums/headers/SmartFeatureTypeEnum.h"

class SmartFeatureTypeEnumUtils {
public:

	static SmartFeatureTypeEnum::SmartFeatureTypeEnum getSmartFeatureTypeEnumByClassName(std::string classNameValue);

private:

	SmartFeatureTypeEnumUtils() {};
	static std::map<SmartFeatureTypeEnum::SmartFeatureTypeEnum, std::vector<std::string>> mappedValues;
};