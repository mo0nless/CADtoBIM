#pragma once

#include <string>
#include <map>

namespace CreateSolidFunctionsEnum {



	enum class CreateSolidFunctionsEnum
	{
		EXTRUDE,
		EXTRUDE_ALONG,
		THICKEN,
		REVOLVE,
		UNDEFINED
	};

	static std::map<CreateSolidFunctionsEnum, std::string> mappedValues;
	CreateSolidFunctionsEnum getCreateSolidFunctionsEnumByClassName(std::string className);
}