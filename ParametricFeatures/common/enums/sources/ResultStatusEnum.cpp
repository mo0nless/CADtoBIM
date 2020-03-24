#include "../headers/ResultStatusEnum.h"

namespace ResultStatusEnum 
{
	const std::map<ResultStatusEnum, std::string> mappedValues =
	{
		{ ResultStatusEnum::SUCCESS,"Success" },
		{ ResultStatusEnum::NO_RESULT,"NoResult" },
		{ ResultStatusEnum::ERROR,"Error" },

	};

	std::string getStringValueOfResultStatusEnum(ResultStatusEnum resultStatusEnum) 
	{
		for (auto const& element : mappedValues) {
			if (element.first == resultStatusEnum) {
				return element.second;
			}
		}

		return std::string();
	}

}
