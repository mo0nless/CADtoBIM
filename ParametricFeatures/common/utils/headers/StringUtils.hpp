#pragma once

#include <string>
#include <Bentley/WString.h>

/**
 *  Utility class for string operations
 */
class StringUtils {
public:

	/**
	 *  Convert WString to std::string
	 *  @param wStringValue[in] 
	 *  @return std:string
	 */
	inline static std::string getString(WString wStringValue);
private:

	/**
	 *  Hide constructor to create a static class
	 */
	StringUtils() {};
};

std::string StringUtils::getString(WString wStringValue) {

	std::wstring ws(wStringValue.c_str());
	std::string stringValue(ws.begin(), ws.end());

	return stringValue;
}