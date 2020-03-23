#include "../headers/PrimitiveTypeEnum.h"

namespace PrimitiveTypeEnum
{
	PrimitiveTypeEnum getPrimitiveTypeEnumByElementDescription(std::string primitiveElementDescription)
	{
		std::map<PrimitiveTypeEnum, std::string> mappedValues = {
			{ PrimitiveTypeEnum::BOX, "Slab" },
			{ PrimitiveTypeEnum::CONE, "Cone" },
			{ PrimitiveTypeEnum::CYLINDER, "Cylinder" },
			{ PrimitiveTypeEnum::SPHERE, "Sphere" },
			{ PrimitiveTypeEnum::TORUS, "Torus" },
			{ PrimitiveTypeEnum::TRUNCATED_CONE, "Truncated Cone" },
			{ PrimitiveTypeEnum::NONE,"" },
		};

		for (auto const& element : mappedValues) {
			if (element.second == primitiveElementDescription) {
				return element.first;
			}
		}
		// TODO add warning log value not found
		return PrimitiveTypeEnum::NONE;
	}
}