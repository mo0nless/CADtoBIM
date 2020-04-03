#pragma once

#include <Bentley/WString.h>

#include <DgnPlatform/DgnECInstance.h>
#include <DgnPlatform/DgnECManager.h>

USING_NAMESPACE_BENTLEY_ECOBJECT;
USING_NAMESPACE_BENTLEY_DGNPLATFORM;

#include <string>

#include "../../../common/utils/headers/SmartFeatureTypeEnumUtils.h"
#include "../../../common/utils/headers/CreateSolidFunctionsEnumUtils.h"
#include "../../../modeler/properties/headers/ReaderProperties.h"

class CreateSolidsOperationPropertiesReaderMapper
{
public:
	static void mapCreateSolidsOperationPropertiesToReaderProperties(std::string labelValue, ECValue eCValue, ReaderProperties & readerProperties);
private:
	CreateSolidsOperationPropertiesReaderMapper();



};
