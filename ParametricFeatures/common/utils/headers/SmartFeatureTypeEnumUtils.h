#pragma once
#include "../../enums/headers/SmartFeatureTypeEnum.h"

#include <map>
#include <string>
#include <vector>

using namespace std;

class SmartFeatureTypeEnumUtils {
public:

	static SmartFeatureTypeEnum getSmartFeatureTypeEnumByClassName(string classNameValue);

private:

	SmartFeatureTypeEnumUtils() {};
	static map<SmartFeatureTypeEnum, vector<string>> mappedValues;
};