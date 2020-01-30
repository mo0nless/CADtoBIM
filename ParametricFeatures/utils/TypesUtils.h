#pragma once

#include "../headers/PropertyTypeValue.h"

class TypesUtils {
	//std::basic_string<char, std::char_traits<char>, std::allocator<char>>
public:
	DRange3d range;
	DVec3d rotation;
	DPoint4d qRotation;
	DPoint3d origin;
	double area, volume, radius;

	TypesUtils();
	TypesUtils(PropertyTypeValue* propsDict);
private:
	template<class Type>
	Type getType(boost::any propValue);
};


template<class Type>
Type TypesUtils::getType(boost::any propValue)
{
	return boost::any_cast<Type>(propValue);
}
