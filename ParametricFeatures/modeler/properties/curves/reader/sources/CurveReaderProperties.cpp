#include "../headers/CurveReaderProperties.h"

CurveReaderProperties::CurveReaderProperties()
{
	this->mCurvesType = CurvesTypeEnum::CurvesTypeEnum::UNDEFINED;
}

void CurveReaderProperties::setCurvesTypeEnum(std::string newDescriptorName)
{
	this->mCurvesType = CurvesTypeEnum::getCurvesTypeEnumByClassName(newDescriptorName);
}

CurvesTypeEnum::CurvesTypeEnum CurveReaderProperties::getCurvesTypeEnum()
{
	return this->mCurvesType;
}
