#pragma once

#include "../../../stdafx.h"
#include <math.h>

namespace Common
{
	namespace Utilities
	{
		struct NumberUtils
		{
			static double NumberUtils::convertCurrentUnitToMeters(double valueInMicroMeters)
			{
				DgnModelRefP dgnModelRef = ISessionMgr::GetActiveDgnModelRefP();
				ModelInfoCP modelInfo = dgnModelRef->GetModelInfoCP();

				double uorPerStorage = modelInfo->GetUorPerStorage();

				return valueInMicroMeters / uorPerStorage;
			}
		};
	}
}