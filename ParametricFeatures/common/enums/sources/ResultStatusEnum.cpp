#include "../headers/ResultStatusEnum.h"

namespace ResultStatusEnum 
{
	std::string getStringValueOfResultStatusEnum(ResultStatusEnum resultStatusEnum) {

		std::map<ResultStatusEnum, std::string> mappedValues =
		{
			{ ResultStatusEnum::SUCCESS,"Success" },
			{ ResultStatusEnum::NO_RESULT,"NoResult" },
			{ ResultStatusEnum::ERROR,"Error" },

		};

		if (mappedValues.find(resultStatusEnum) == mappedValues.end()) {
			return std::string();
		}
		return mappedValues[resultStatusEnum];
	}

}
