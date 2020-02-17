#pragma once

#include <string>
#include "ResultStatusEnum.h"

/**
 *  Class used to return status and message after an execution
 */
class ResultStatus {

private:
	ResultStatusEnum resultStatusEnum;
	std::string errorText;
public:
	ResultStatus();
	ResultStatus(ResultStatusEnum newResultStatusEnum);
	ResultStatus(ResultStatusEnum newResultStatusEnum, std::string newErrorText);

	ResultStatusEnum getResultStatusEnum();
	std::string getErrorText();
};