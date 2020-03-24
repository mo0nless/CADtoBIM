#pragma once


#include <map>
#include <string>

namespace CreateSolidFunctionsEnum {

	enum class CreateSolidFunctionsEnum
	{
		EXTRUDE,
		EXTRUDE_ALONG,
		THICKEN,
		REVOLVE,
		UNDEFINED
	};

	CreateSolidFunctionsEnum getCreateSolidFunctionsEnumByClassName(std::string className);
}