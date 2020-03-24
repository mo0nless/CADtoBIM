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

	ReaderPropertiesEnum getElementPropertiesEnumByStringValue(std::string stringValue);
}