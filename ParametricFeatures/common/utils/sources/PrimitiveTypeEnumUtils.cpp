#include "../headers/PrimitiveTypeEnumUtils.h"


std::map<PrimitiveTypeEnum, std::string> PrimitiveTypeEnumUtils::mappedValues = {
	{ PrimitiveTypeEnum::BOX, "Slab" },
	{ PrimitiveTypeEnum::CONE, "Cone" },
	{ PrimitiveTypeEnum::CYLINDER, "Cylinder" },
	{ PrimitiveTypeEnum::SPHERE, "Sphere" },
	{ PrimitiveTypeEnum::TORUS, "Torus" },
	{ PrimitiveTypeEnum::TRUNCATED_CONE, "Truncated Cone" },
	{ PrimitiveTypeEnum::ROTATIONAL_SWEEP, "Rotational Sweep" },
	{ PrimitiveTypeEnum::NONE,"" },
};

