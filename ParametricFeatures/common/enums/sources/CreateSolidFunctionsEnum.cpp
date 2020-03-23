
#include "../headers/CreateSolidFunctionsEnum.h"

namespace CreateSolidFunctionsEnum {
	
	CreateSolidFunctionsEnum getCreateSolidFunctionsEnumByClassName(std::string className) 
	{
		std::map<CreateSolidFunctionsEnum, std::string> mappedValues = {
			{ CreateSolidFunctionsEnum::REVOLVE, "Revolve" },
			{ CreateSolidFunctionsEnum::EXTRUDE, "Extrude" },
			{ CreateSolidFunctionsEnum::THICKEN, "Thiken" },
			{ CreateSolidFunctionsEnum::EXTRUDE_ALONG, "Extrude Along" },
			{ CreateSolidFunctionsEnum::UNDEFINED, "" },
		};

		for (auto const& element : mappedValues) {
			if (element.second == className) {
				return element.first;
			}
		}
		// TODO add warning log value not found
		return CreateSolidFunctionsEnum::UNDEFINED;
	}
}