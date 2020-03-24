#pragma once

#include <string>
#include <map>
#include <vector>

namespace SmartFeatureTypeEnum {


	enum class SmartFeatureTypeEnum {
		BOOLEAN_FEATURE,
		CREATE_SOLIDS,
		//COMPLEX_STRING_ELEMENT,
		UNDEFINED
	};

	SmartFeatureTypeEnum getSmartFeatureTypeEnumByClassName(std::string classNameValue);
}