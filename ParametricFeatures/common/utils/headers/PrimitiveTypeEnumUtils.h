#pragma once

#include <map>
#include <string>

#include "../../enums/headers/PrimitiveTypeEnum.h"



//TODO [MP] to be deleted
/**
*  Class used to contain the immutable map between ReaderPropertiesEnum and the string value from the modeler
*/
class PrimitiveTypeEnumUtils {


private:
	/**
	* Hide contructor to have a static class
	*/
	PrimitiveTypeEnumUtils() {};

	/**
	* map contains relevant and needed primitives, enum as keys and values as the string(label) value from modeler
	*/
	static std::map<PrimitiveTypeEnum, std::string> mappedValues;

};