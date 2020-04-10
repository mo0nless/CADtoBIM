#include "../headers/CreateSolidFunctionsEnumUtils.h"


std::map<CreateSolidFunctionsEnum, std::string> CreateSolidFunctionsEnumUtils::mappedValues = {
	{ CreateSolidFunctionsEnum::REVOLVE, "Revolve" },
	{ CreateSolidFunctionsEnum::EXTRUDE, "Extrude" },
	{ CreateSolidFunctionsEnum::EXTRUDE_ALONG, "ExtrudeAlong" },
	{ CreateSolidFunctionsEnum::UNDEFINED, "" },
};

std::map<CreateSolidPropertiesEnum, std::string> CreateSolidFunctionsEnumUtils::mappedValuesProps = {

	{ CreateSolidPropertiesEnum::THICKNESS,"Thickness" },
	{ CreateSolidPropertiesEnum::DISTANCE,"Distance" },
	{ CreateSolidPropertiesEnum::NONE,"" },
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

CreateSolidPropertiesEnum CreateSolidFunctionsEnumUtils::getSolidPropertiesEnumByClassName(std::string className)
{
	for (auto const& element : mappedValuesProps) {
		if (element.second == className) {
			return element.first;
		}
	}
	// TODO add warning log value not found
	return CreateSolidPropertiesEnum::NONE;
}