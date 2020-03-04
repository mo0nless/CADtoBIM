#pragma once

#include <map>
#include <string>

#include "../../enums/headers/PrimitiveTypeEnum.h"

/**
*  Class used to contain the immutable map between ReaderPropertiesEnum and the string value from the modeler
*/
class PrimitiveTypeEnumUtils {
public:

	/**
	*  static method to retrieve enum value based on the string(label) value received from the modeler
	*  @param stringValue[in]
	*  @return PrimitiveTypeEnum
	*/
	static PrimitiveTypeEnum::PrimitiveTypeEnum getPrimitiveTypeEnumByElementDescription(std::string primitiveElementDescription);

private:
	/**
	* Hide contructor to have a static class
	*/
	PrimitiveTypeEnumUtils() {};

	/**
	* map contains relevant and needed primitives, enum as keys and values as the string(label) value from modeler
	*/
	static std::map<PrimitiveTypeEnum::PrimitiveTypeEnum, std::string> mappedValues;

};