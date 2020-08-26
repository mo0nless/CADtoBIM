#pragma once

#include <string>
#include "../../enums/headers/ResultStatusEnum.h"

/**
 *  Class used to return status and message after an execution
 */
template <class T>
class ResultStatus {

private:
	ResultStatusEnum::ResultStatusEnum mResultStatusEnum;
	std::string mErrorText;
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
	this->mResultStatusEnum = ResultStatusEnum::ResultStatusEnum::SUCCESS;
	this->mErrorText = std::string();
}

template<class T>
inline ResultStatus<T>::ResultStatus(ResultStatusEnum::ResultStatusEnum newResultStatusEnum)
{
	this->mResultStatusEnum = newResultStatusEnum;
	this->mErrorText = std::string();
}

template<class T>
inline ResultStatus<T>::ResultStatus(ResultStatusEnum::ResultStatusEnum newResultStatusEnum, std::string newErrorText)
{
	this->mResultStatusEnum = newResultStatusEnum;
	this->mErrorText = newErrorText;
}

template<class T>
inline ResultStatusEnum::ResultStatusEnum ResultStatus<T>::getResultStatusEnum()
{
	return this->mResultStatusEnum;
}

template<class T>
inline std::string ResultStatus<T>::getErrorText()
{
	return this->mErrorText;
}
