#pragma once

#include <Bentley/WString.h>

#include <DgnPlatform/DgnECInstance.h>
#include <DgnPlatform/DgnECManager.h>

USING_NAMESPACE_BENTLEY_ECOBJECT;
USING_NAMESPACE_BENTLEY_DGNPLATFORM;

#include <string>

#include "../../../common/utils/headers/ReaderPropertiesEnumUtils.h"
#include "../../../modeler/properties/headers/ReaderProperties.h"


class BooleanOperationReaderPropertiesMapper {

private:
	BooleanOperationReaderPropertiesMapper() {};

public:
	static void mapBooleanOperationReaderPropertiesToReaderProperties(std::string labelValue, ECValue eCValue, ReaderProperties &readerProperties);
};