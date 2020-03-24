#pragma once

#include <map>
#include <string>

#include "../../enums/headers/CreateSolidFunctionsEnum.h"


class CreateSolidFunctionsEnumUtils {

private:
	CreateSolidFunctionsEnumUtils() {};
	static std::map<CreateSolidFunctionsEnum::CreateSolidFunctionsEnum, std::string> mappedValues;

public:
	CreateSolidFunctionsEnum::CreateSolidFunctionsEnum getCreateSolidFunctionsEnumByClassName(std::string className);

};