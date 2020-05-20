#pragma once


#include <map>
#include <string>


	enum class CreateSolidFunctionsEnum
	{
		EXTRUDE,
		EXTRUDE_ALONG,
		REVOLVE,
		THIKEN,
		UNDEFINED
	};

	enum class CreateSolidPropertiesEnum
	{
		THICKNESS,
		DISTANCE,
		NONE,
	};