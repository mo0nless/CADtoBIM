#pragma once

namespace Common
{
	namespace Enums
	{
		enum class CreateSolidFunctionsEnum
		{
			EXTRUDE,
			EXTRUDE_ALONG,
			REVOLVE,
			THICKEN,
			UNDEFINED
		};

		enum class CreateSolidPropertiesEnum
		{
			THICKNESS,
			DISTANCE,
			NONE,
		};
	}
}