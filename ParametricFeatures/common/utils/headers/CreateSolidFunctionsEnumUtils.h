#pragma once

#include <map>
#include <string>

#include "../../enums/headers/CreateSolidFunctionsEnum.h"

using namespace std;

class CreateSolidFunctionsEnumUtils {

private:
	CreateSolidFunctionsEnumUtils() {};
	static map<CreateSolidFunctionsEnum, string> mappedValues;
	static map<CreateSolidPropertiesEnum, string> mappedValuesProps;

public:
	static CreateSolidFunctionsEnum getCreateSolidFunctionsEnumByClassName(string className);
	static CreateSolidPropertiesEnum getSolidPropertiesEnumByClassName(string className);
};