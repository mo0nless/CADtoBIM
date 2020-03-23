#pragma once

#include <string>
#include "../../../enums/headers/ResultStatusEnum.h"

/**
 *  Class used to return status and message after an execution
 */
template <class T>
class ResultStatus {

private:
	ResultStatusEnum::ResultStatusEnum resultStatusEnum;
	std::string errorText;
public:
	ResultStatus<T>();
	ResultStatus<T>(ResultStatusEnum::ResultStatusEnum newResultStatusEnum);
	ResultStatus<T>(ResultStatusEnum::ResultStatusEnum newResultStatusEnum, std::string newErrorText);

	ResultStatusEnum::ResultStatusEnum getResultStatusEnum();
	std::string getErrorText();
};

template<class T>
inline ResultStatus<T>::ResultStatus()
{
	this->resultStatusEnum = ResultStatusEnum::ResultStatusEnum::SUCCESS;
	this->errorText = std::string();
}

template<class T>
inline ResultStatus<T>::ResultStatus(ResultStatusEnum::ResultStatusEnum newResultStatusEnum)
{
	this->resultStatusEnum = newResultStatusEnum;
	this->errorText = std::string();
}

template<class T>
inline ResultStatus<T>::ResultStatus(ResultStatusEnum::ResultStatusEnum newResultStatusEnum, std::string newErrorText)
{
	this->resultStatusEnum = newResultStatusEnum;
	this->errorText = newErrorText;
}

template<class T>
inline ResultStatusEnum::ResultStatusEnum ResultStatus<T>::getResultStatusEnum()
{
	return this->resultStatusEnum;
}

template<class T>
inline std::string ResultStatus<T>::getErrorText()
{
	return this->errorText;
}
