#pragma once

#include "../stdafx.h"
#include "StringUtils.h"

StringUtils::StringUtils()
{
}

std::string StringUtils::getString(WString wstringValue) {

	std::wstring ws(wstringValue.c_str());
	std::string stringValue(ws.begin(), ws.end());

	return stringValue;
}
