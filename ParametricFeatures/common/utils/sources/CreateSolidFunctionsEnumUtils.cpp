#include "../headers/CreateSolidFunctionsEnumUtils.h"


std::map<CreateSolidFunctionsEnum::CreateSolidFunctionsEnum, std::string> CreateSolidFunctionsEnumUtils::mappedValues = {
	{ CreateSolidFunctionsEnum::CreateSolidFunctionsEnum::REVOLVE, "Revolve" },
	{ CreateSolidFunctionsEnum::CreateSolidFunctionsEnum::EXTRUDE, "Extrude" },
	{ CreateSolidFunctionsEnum::CreateSolidFunctionsEnum::THICKEN, "Thiken" },
	{ CreateSolidFunctionsEnum::CreateSolidFunctionsEnum::EXTRUDE_ALONG, "Extrude Along" },
	{ CreateSolidFunctionsEnum::CreateSolidFunctionsEnum::UNDEFINED, "" },
};



CreateSolidFunctionsEnum::CreateSolidFunctionsEnum CreateSolidFunctionsEnumUtils::getCreateSolidFunctionsEnumByClassName(std::string className)
{
	for (auto const& element : mappedValues) {
		if (element.second == className) {
			return element.first;
		}
	}
	// TODO add warning log value not found
	return CreateSolidFunctionsEnum::CreateSolidFunctionsEnum::UNDEFINED;
}