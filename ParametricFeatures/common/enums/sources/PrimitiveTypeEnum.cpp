#include "../headers/PrimitiveTypeEnum.h"

namespace PrimitiveTypeEnum
{
	const std::map<PrimitiveTypeEnum, std::string> mappedValues = {
		{ PrimitiveTypeEnum::BOX, "Slab" },
		{ PrimitiveTypeEnum::CONE, "Cone" },
		{ PrimitiveTypeEnum::CYLINDER, "Cylinder" },
		{ PrimitiveTypeEnum::SPHERE, "Sphere" },
		{ PrimitiveTypeEnum::TORUS, "Torus" },
		{ PrimitiveTypeEnum::TRUNCATED_CONE, "Truncated Cone" },
		{ PrimitiveTypeEnum::NONE,"" },
	};

	PrimitiveTypeEnum getPrimitiveTypeEnumByElementDescription(std::string primitiveElementDescription)
	{
		for (auto const& element : mappedValues) {
			if (element.second == primitiveElementDescription) {
				return element.first;
			}
		}
		// TODO add warning log value not found
		return PrimitiveTypeEnum::NONE;
	}
}