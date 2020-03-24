#pragma once

#include "../../../../../common/enums/headers/CurvesTypeEnum.h"
//#include "../../../curves/graphic/headers/CurveGraphicProperties.h"

class CurveReaderProperties
{
private:
	CurvesTypeEnum::CurvesTypeEnum mCurvesType;

public:
	CurveReaderProperties();

	void setCurvesTypeEnum(std::string newDescriptorName);
	CurvesTypeEnum::CurvesTypeEnum getCurvesTypeEnum();

};