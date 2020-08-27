#pragma once

#include <string>
#include <Bentley/WString.h>

using namespace std;

/**
 *  Utility class for string operations
 */
struct StringUtils {
	/**
	*  Convert WString to string
	*  @param wStringValue[in]
	*  @return std:string
	*/
	inline static string getString(WString wStringValue) {

		wstring ws(wStringValue.c_str());
		string stringValue(ws.begin(), ws.end());

		return stringValue;
	}

	/**
	*  Normalize string, remove special characters, otherwise exception thrown in IfcParse
	*  @param stringValue[in]
	*  @return std:string
	*/
	inline static string getNormalizedString(string stringValue) {

		stringValue.resize(remove_if(stringValue.begin(),
			stringValue.end(), [](char x) {return !isalnum(x) && !isspace(x) && static_cast<unsigned char>(x) > 127; }) - stringValue.begin());

		return stringValue;
	}

	inline static string getNormalizedString(WString wStringValue) {

		return getNormalizedString(getString(wStringValue));
	}
};

