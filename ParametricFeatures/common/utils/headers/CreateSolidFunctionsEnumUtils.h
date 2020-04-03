#pragma once

#include <map>
#include <string>

#include "../../enums/headers/CreateSolidFunctionsEnum.h"


class CreateSolidFunctionsEnumUtils {

private:
	CreateSolidFunctionsEnumUtils() {};
	static std::map<CreateSolidFunctionsEnum, std::string> mappedValues;
	static std::map<CreateSolidPropertiesEnum, std::string> mappedValuesProps;

public:
	static CreateSolidFunctionsEnum getCreateSolidFunctionsEnumByClassName(std::string className);
	static CreateSolidPropertiesEnum getSolidPropertiesEnumByClassName(std::string className);
};