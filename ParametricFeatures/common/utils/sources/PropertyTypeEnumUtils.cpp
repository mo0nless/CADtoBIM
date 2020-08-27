#include "../headers/PropertyTypeEnumUtils.h"

const map<PropertyTypeEnum, string> PropertyTypeEnumUtils::mappedValues =
{
	{ PropertyTypeEnum::BINARY,"binary" },
	{ PropertyTypeEnum::INTEGER,"int" },
	{ PropertyTypeEnum::LONG,"long" },
	{ PropertyTypeEnum::DOUBLE,"double" },
	{ PropertyTypeEnum::BOOLEAN,"boolean" },
	{ PropertyTypeEnum::STRING,"string" },
	{ PropertyTypeEnum::POINT2D,"point2d" },
	{ PropertyTypeEnum::POINT3D,"point3d" },
	{ PropertyTypeEnum::DATETIME,"dateTime" }
};

PropertyTypeEnum PropertyTypeEnumUtils::getEnumByStringValue(string stringValue)
{
	for (auto const& element : mappedValues) {
		if (element.second == stringValue) {
			return element.first;
		}
	}
	return PropertyTypeEnum::UNDEFINED;
}
