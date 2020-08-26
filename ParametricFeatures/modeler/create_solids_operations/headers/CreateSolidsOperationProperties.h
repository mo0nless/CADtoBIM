#pragma once

#include "RevolveReaderProperties.h"
#include "ExtrusionReaderProperties.h"
#include "../../../../common/utils/headers/CreateSolidFunctionsEnumUtils.h"
//#include "../../../../../common/enums/headers/CreateSolidFunctionsEnum.h"

class CreateSolidsOperationProperties {

private:
	CreateSolidFunctionsEnum mCreateSolidFunctionsEnum;

	RevolveReaderProperties* revolveReaderProperties;
	ExtrusionReaderProperties* extrusionReaderProperties;

public:
	CreateSolidsOperationProperties();

	CreateSolidFunctionsEnum getCreateSolidTypeEnum();
	void setCreateSolidTypeEnum(CreateSolidFunctionsEnum value);

	bool tryGetRevolveReaderProperties(RevolveReaderProperties*& revolveReaderPropertiesR);
	void setRevolveReaderProperties(RevolveReaderProperties* newRevolveReaderProperties);

	bool tryGetExtrusionReaderProperties(ExtrusionReaderProperties*& extrusionReaderPropertiesR);
	void setExtrusionReaderProperties(ExtrusionReaderProperties* newExtrusionReaderProperties);

};