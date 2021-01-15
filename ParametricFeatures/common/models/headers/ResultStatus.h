#pragma once

/**
 * @file ResultStatus.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../../enums/headers/ResultStatusEnum.h"

using namespace std;
using namespace Common::Enums;

/**
 * @brief Class used to return status and message after an execution
 * 
 * @tparam T 
 * 
 * @remark At the moment is not used in the project
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
