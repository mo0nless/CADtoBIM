#include "../headers/ResultStatusEnum.h"

namespace ResultStatusEnum 
{
	const map<ResultStatusEnum, string> mappedValues =
	{
		{ ResultStatusEnum::SUCCESS,"Success" },
		{ ResultStatusEnum::NO_RESULT,"NoResult" },
		{ ResultStatusEnum::ERROR,"Error" },

	};

	string getStringValueOfResultStatusEnum(ResultStatusEnum resultStatusEnum) 
	{
		for (auto const& element : mappedValues) {
			if (element.first == resultStatusEnum) {
				return element.second;
			}
		}

		return string();
	}

}
