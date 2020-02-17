#pragma once

#include <Bentley/WString.h>

#include <DgnPlatform/DgnECInstance.h>
#include <DgnPlatform/DgnECManager.h>

USING_NAMESPACE_BENTLEY_ECOBJECT;
USING_NAMESPACE_BENTLEY_DGNPLATFORM;


#include "../../../modeler/properties/headers/ReaderProperties.h"
#include "../../../common/utils/StringUtils.hpp"
#include "../../../common/properties/headers/ReaderPropertiesEnumUtils.h"

class ReaderPropertiesMapper {
	
private:
	ReaderPropertiesMapper() {};

public:
	static void mapECPropertiesToElementProperties(DgnElementECInstanceP dgnElementECInstanceP, ReaderProperties &elementProperties);

	static void mapPropertyToElementPropertiesMember(std::string labelValue, ECValue eCValue, ReaderProperties &elementProperties);
};