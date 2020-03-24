#include "../headers/PrimitiveTypeEnumUtils.h"


std::map<PrimitiveTypeEnum, std::string> PrimitiveTypeEnumUtils::mappedValues = {
	{ PrimitiveTypeEnum::BOX, "Slab" },
	{ PrimitiveTypeEnum::CONE, "Cone" },
	{ PrimitiveTypeEnum::CYLINDER, "Cylinder" },
	{ PrimitiveTypeEnum::SPHERE, "Sphere" },
	{ PrimitiveTypeEnum::TORUS, "Torus" },
	{ PrimitiveTypeEnum::TRUNCATED_CONE, "Truncated Cone" },
	{ PrimitiveTypeEnum::NONE,"" },
};

PrimitiveTypeEnum PrimitiveTypeEnumUtils::getPrimitiveTypeEnumByElementDescription(std::string primitiveElementDescription)
{
	for (auto const& element : mappedValues) {
		if (element.second == primitiveElementDescription) {
			return element.first;
		}
	}
	// TODO add warning log value not found
	return PrimitiveTypeEnum::NONE;
}
