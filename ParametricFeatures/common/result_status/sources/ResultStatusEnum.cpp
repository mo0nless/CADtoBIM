#include "../headers/ResultStatusEnum.h"

std::map<ResultStatusEnum, std::string> mappedValues =
{
	{ ResultStatusEnum::SUCCESS,"Success" },
	{ ResultStatusEnum::NO_RESULT,"NoResult" },
	{ ResultStatusEnum::ERROR,"Error" },

};

std::string getStringValueOfResultStatusEnum(ResultStatusEnum resultStatusEnum) {
	if (mappedValues.find(resultStatusEnum) == mappedValues.end()) {
		return std::string();
	}
	return mappedValues[resultStatusEnum];
}