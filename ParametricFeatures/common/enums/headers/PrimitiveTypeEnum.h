#pragma once

#include <string>
#include <map>

namespace PrimitiveTypeEnum {

	enum class PrimitiveTypeEnum {

		BOX,
		CONE,
		CYLINDER,
		PYRAMID,
		SPHERE,
		TORUS,
		TRUNCATED_CONE,
		NONE

	};

	PrimitiveTypeEnum getPrimitiveTypeEnumByElementDescription(std::string className);
}