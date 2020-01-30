#include"TypesUtils.h"

TypesUtils::TypesUtils()
{
}

TypesUtils::TypesUtils(PropertyTypeValue* propsDict)
{
	std::string valueType = propsDict->getPropertyType();
	if (valueType == "DRange3d") { TypesUtils::range = TypesUtils::getType<DRange3d>(propsDict->getPropertyValue()); }
}



