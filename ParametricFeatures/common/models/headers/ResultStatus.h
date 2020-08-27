#pragma once

#include "../../enums/headers/ResultStatusEnum.h"

using namespace std;

/**
 *  Class used to return status and message after an execution
 */
template <class T>
class ResultStatus {

private:
	ResultStatusEnum::ResultStatusEnum mResultStatusEnum;
	string mErrorText;
public:
	ResultStatus<T>();
	ResultStatus<T>(ResultStatusEnum::ResultStatusEnum newResultStatusEnum);
	ResultStatus<T>(ResultStatusEnum::ResultStatusEnum newResultStatusEnum, string newErrorText);

	ResultStatusEnum::ResultStatusEnum getResultStatusEnum();
	string getErrorText();
};

template<class T>
inline ResultStatus<T>::ResultStatus()
{
	this->mResultStatusEnum = ResultStatusEnum::ResultStatusEnum::SUCCESS;
	this->mErrorText = string();
}

template<class T>
inline ResultStatus<T>::ResultStatus(ResultStatusEnum::ResultStatusEnum newResultStatusEnum)
{
	this->mResultStatusEnum = newResultStatusEnum;
	this->mErrorText = string();
}

template<class T>
inline ResultStatus<T>::ResultStatus(ResultStatusEnum::ResultStatusEnum newResultStatusEnum, string newErrorText)
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
inline string ResultStatus<T>::getErrorText()
{
	return this->mErrorText;
}
