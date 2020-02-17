#pragma once

#include <string>
#include "ResultStatusEnum.h"

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