#pragma once

#include <string>
#include <map>
#include <vector>

namespace SmartFeatureContainerTypeEnum {


	enum class SmartFeatureContainerTypeEnum {
		BOOLEAN_FEATURE,
		CREATE_SOLIDS,
		UNDEFINED
	};

	static std::map<SmartFeatureContainerTypeEnum, std::vector<std::string>> mappedValues;
	SmartFeatureContainerTypeEnum getSmartFeatureContainerTypeEnumByStringValue(std::string classNameValue);


}