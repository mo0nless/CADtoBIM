#include "../headers/PrimitiveTypeEnumUtils.h"


std::map<PrimitiveTypeEnum::PrimitiveTypeEnum, std::string> PrimitiveTypeEnumUtils::mappedValues = {
	{ PrimitiveTypeEnum::PrimitiveTypeEnum::BOX, "Slab" },
	{ PrimitiveTypeEnum::PrimitiveTypeEnum::CONE, "Cone" },
	{ PrimitiveTypeEnum::PrimitiveTypeEnum::CYLINDER, "Cylinder" },
	{ PrimitiveTypeEnum::PrimitiveTypeEnum::SPHERE, "Sphere" },
	{ PrimitiveTypeEnum::PrimitiveTypeEnum::TORUS, "Torus" },
	{ PrimitiveTypeEnum::PrimitiveTypeEnum::TRUNCATED_CONE, "Truncated Cone" },
	{ PrimitiveTypeEnum::PrimitiveTypeEnum::NONE,"" },
};

PrimitiveTypeEnum::PrimitiveTypeEnum PrimitiveTypeEnumUtils::getPrimitiveTypeEnumByElementDescription(std::string primitiveElementDescription)
{
	for (auto const& element : mappedValues) {
		if (element.second == primitiveElementDescription) {
			return element.first;
		}
	}
	// TODO add warning log value not found
	return PrimitiveTypeEnum::PrimitiveTypeEnum::NONE;
}
