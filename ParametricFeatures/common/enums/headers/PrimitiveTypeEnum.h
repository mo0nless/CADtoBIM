#pragma once

#include <map>
#include <string>

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

	PrimitiveTypeEnum getPrimitiveTypeEnumByElementDescription(std::string primitiveElementDescription);
}
