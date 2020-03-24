#pragma once

#include <string>
#include <map>
#include <vector>

namespace SmartFeatureTypeEnum {

enum class SmartFeatureTypeEnum {
	BOOLEAN_FEATURE,
	CREATE_SOLIDS,
	PIPES,
	UNDEFINED
};

	SmartFeatureTypeEnum getSmartFeatureTypeEnumByClassName(std::string classNameValue);
}