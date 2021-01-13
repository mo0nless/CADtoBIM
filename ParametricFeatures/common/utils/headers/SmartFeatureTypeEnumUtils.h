#pragma once
#include "../../enums/headers/SmartFeatureTypeEnum.h"

#include <map>
#include <string>
#include <vector>

using namespace std;
using namespace Common::Enums;

namespace Common
{
	namespace Utilities
	{
		class SmartFeatureTypeEnumUtils {
		public:

			static SmartFeatureTypeEnum getSmartFeatureTypeEnumByClassName(string classNameValue);

		private:

			SmartFeatureTypeEnumUtils() {};
			static map<SmartFeatureTypeEnum, vector<string>> mappedValues;
		};
	}
}