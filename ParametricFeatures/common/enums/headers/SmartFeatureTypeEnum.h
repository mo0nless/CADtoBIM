#pragma once

#include <string>
#include <map>
#include <vector>

namespace SmartFeatureTypeEnum {

enum class SmartFeatureTypeEnum {
	BOOLEAN_FEATURE,
	CREATE_SOLIDS,
	UNDEFINED
};

	SmartFeatureTypeEnum getSmartFeatureTypeEnumByClassName(std::string classNameValue);
}