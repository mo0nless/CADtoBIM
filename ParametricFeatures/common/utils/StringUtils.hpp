#pragma once

#include <string>
#include <Bentley/WString.h>

class StringUtils {
public:
	inline static std::string getString(WString wStringValue);
private:
	StringUtils();
};

std::string StringUtils::getString(WString wStringValue) {

	std::wstring ws(wStringValue.c_str());
	std::string stringValue(ws.begin(), ws.end());

	return stringValue;
}