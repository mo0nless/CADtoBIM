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

	CreateSolidFunctionsEnum getCreateSolidFunctionsEnumByClassName(std::string className);
}