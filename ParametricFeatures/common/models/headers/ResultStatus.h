#pragma once

#include "../../enums/headers/ResultStatusEnum.h"

using namespace std;
using namespace Common::Enums;

/**
 *  Class used to return status and message after an execution
 */
template <class T>
class ResultStatus {

private:
	Enums::ResultStatusEnum mResultStatusEnum;
	string mErrorText;
public:
	ResultStatus<T>();
	ResultStatus<T>(Enums::ResultStatusEnum newResultStatusEnum);
	ResultStatus<T>(Enums::ResultStatusEnum newResultStatusEnum, string newErrorText);

	Enums::ResultStatusEnum getResultStatusEnum();
	string getErrorText();
};

template<class T>
inline ResultStatus<T>::ResultStatus()
{
	this->mResultStatusEnum = Enums::ResultStatusEnum::SUCCESS;
	this->mErrorText = string();
}

template<class T>
inline ResultStatus<T>::ResultStatus(Enums::ResultStatusEnum newResultStatusEnum)
{
	this->mResultStatusEnum = newResultStatusEnum;
	this->mErrorText = string();
}

template<class T>
inline ResultStatus<T>::ResultStatus(Enums::ResultStatusEnum newResultStatusEnum, string newErrorText)
{
	this->mResultStatusEnum = newResultStatusEnum;
	this->mErrorText = newErrorText;
}

template<class T>
inline Enums::ResultStatusEnum ResultStatus<T>::getResultStatusEnum()
{
	return this->mResultStatusEnum;
}

template<class T>
inline string ResultStatus<T>::getErrorText()
{
	return this->mErrorText;
}
