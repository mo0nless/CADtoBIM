#pragma once

#include <string>
#include <map>

namespace ReaderPropertiesEnum {


	/**
	 * Enum with the list of needed Reader Properties
	 */
	enum class ReaderPropertiesEnum {
		NODE_ID,
		BOOLEAN_FUNCTION,
		ROTATION,
		NONE
	};

	/**
	*  static method to retrieve enum value based on the string(label) value received from the modeler
	*  @param stringValue[in]
	*  @return ReaderPropertiesEnum
	*/
	ReaderPropertiesEnum getElementPropertiesEnumByStringValue(std::string stringValue);
}