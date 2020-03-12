#pragma once

#include <string>
#include "../../../enums/headers/ResultStatusEnum.h"

/**
 *  Class used to return status and message after an execution
 */
template <class T>
class ResultStatus {

private:
	ResultStatusEnum resultStatusEnum;
	std::string errorText;
public:
	ResultStatus<T>();
	ResultStatus<T>(ResultStatusEnum newResultStatusEnum);
	ResultStatus<T>(ResultStatusEnum newResultStatusEnum, std::string newErrorText);

	ResultStatusEnum getResultStatusEnum();
	std::string getErrorText();
};

template<class T>
inline ResultStatus<T>::ResultStatus()
{
	this->resultStatusEnum = ResultStatusEnum::SUCCESS;
	this->errorText = std::string();
}

template<class T>
inline ResultStatus<T>::ResultStatus(ResultStatusEnum newResultStatusEnum)
{
	this->resultStatusEnum = newResultStatusEnum;
	this->errorText = std::string();
}

template<class T>
inline ResultStatus<T>::ResultStatus(ResultStatusEnum newResultStatusEnum, std::string newErrorText)
{
	this->resultStatusEnum = newResultStatusEnum;
	this->errorText = newErrorText;
}

template<class T>
inline ResultStatusEnum ResultStatus<T>::getResultStatusEnum()
{
	return this->resultStatusEnum;
}

template<class T>
inline std::string ResultStatus<T>::getErrorText()
{
	return this->errorText;
}
