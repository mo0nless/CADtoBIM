#pragma once

#include <map>
#include <string>

#include "../properties/headers/ReaderPropertiesEnum.h"

/**
 *  Class used to contain the immutable map between ReaderPropertiesEnum and the string value from the modeler
 */
class ReaderPropertiesEnumUtils {
public:

	/**
	 *  static method to retrieve enum value based on the string(label) value received from the modeler
	 *  @param stringValue[in]
	 *  @return ReaderPropertiesEnum
	 */
	static ReaderPropertiesEnum::ReaderPropertiesEnum getElementPropertiesEnumByStringValue(std::string stringValue);

private:
	/** 
	 * Hide contructor to have a static class
	 */
	ReaderPropertiesEnumUtils() {};

	/**
	 * map contains relevant and needed properties from the reader, enum as keys and values as the string(label) value from modeler
	 */
	static std::map<ReaderPropertiesEnum::ReaderPropertiesEnum, std::string> mappedValues;

};