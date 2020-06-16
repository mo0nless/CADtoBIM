#pragma once

struct NumberUtils
{
	static double NumberUtils::convertMicrometersToMetters(double valueInMicroMeters)
	{
		return valueInMicroMeters / 1000000;
	}
};