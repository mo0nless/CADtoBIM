#pragma once

#include <string>
#include <Bentley/WString.h>

/**
 *  Utility class for string operations
 */
struct StringUtils {
	/**
	*  Convert WString to std::string
	*  @param wStringValue[in]
	*  @return std:string
	*/
	inline static std::string getString(WString wStringValue) {

		std::wstring ws(wStringValue.c_str());
		std::string stringValue(ws.begin(), ws.end());

		return stringValue;
	}

	/**
	*  Normalize string, remove special characters, otherwise exception thrown in IfcParse
	*  @param stringValue[in]
	*  @return std:string
	*/
	inline static std::string getNormalizedString(std::string stringValue) {

		stringValue.resize(remove_if(stringValue.begin(),
			stringValue.end(), [](char x) {return !isalnum(x) && !isspace(x) && static_cast<unsigned char>(x) > 127; }) - stringValue.begin());

		return stringValue;
	}

	inline static std::string getNormalizedString(WString wStringValue) {

		return getNormalizedString(getString(wStringValue));
	}
};

