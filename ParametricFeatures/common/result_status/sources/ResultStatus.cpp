
#include "../headers/ResultStatus.h"

ResultStatus::ResultStatus()
{
	this->resultStatusEnum = ResultStatusEnum::SUCCESS;
	this->errorText = std::string();
}

ResultStatus::ResultStatus(ResultStatusEnum newResultStatusEnum)
{
	this->resultStatusEnum = newResultStatusEnum;
	this->errorText = std::string();
}

ResultStatus::ResultStatus(ResultStatusEnum newResultStatusEnum, std::string newErrorText)
{
	this->resultStatusEnum = newResultStatusEnum;
	this->errorText = newErrorText;
}

ResultStatusEnum ResultStatus::getResultStatusEnum()
{
	return this->resultStatusEnum;
}

std::string ResultStatus::getErrorText()
{
	return this->errorText;
}
