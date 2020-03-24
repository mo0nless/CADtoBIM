#include "../headers/CreateSolidFunctionsEnumUtils.h"


std::map<CreateSolidFunctionsEnum, std::string> CreateSolidFunctionsEnumUtils::mappedValues = {
	{ CreateSolidFunctionsEnum::REVOLVE, "Revolve" },
	{ CreateSolidFunctionsEnum::EXTRUDE, "Extrude" },
	{ CreateSolidFunctionsEnum::THICKEN, "Thiken" },
	{ CreateSolidFunctionsEnum::EXTRUDE_ALONG, "Extrude Along" },
	{ CreateSolidFunctionsEnum::UNDEFINED, "" },
};



CreateSolidFunctionsEnum CreateSolidFunctionsEnumUtils::getCreateSolidFunctionsEnumByClassName(std::string className)
{
	for (auto const& element : mappedValues) {
		if (element.second == className) {
			return element.first;
		}
	}
	// TODO add warning log value not found
	return CreateSolidFunctionsEnum::UNDEFINED;
}