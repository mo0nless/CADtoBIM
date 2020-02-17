#pragma once

#include <map>
#include <string>

#include "ReaderPropertiesEnum.h"

class ReaderPropertiesEnumUtils {
public:

	static ReaderPropertiesEnum::ReaderPropertiesEnum getElementPropertiesEnumByStringValue(std::string stringValue);

private:
	ReaderPropertiesEnumUtils() {};
	static std::map<ReaderPropertiesEnum::ReaderPropertiesEnum, std::string> mappedValues;

};