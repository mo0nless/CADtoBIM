#pragma once

#include <Bentley/WString.h>

#include <DgnPlatform/DgnECInstance.h>
#include <DgnPlatform/DgnECManager.h>

USING_NAMESPACE_BENTLEY_ECOBJECT;
USING_NAMESPACE_BENTLEY_DGNPLATFORM;


#include "../../../modeler/properties/headers/ReaderProperties.h"
#include "../../../common/utils/headers/StringUtils.hpp"
#include "../../../common/utils/headers/ReaderPropertiesEnumUtils.h"

/**
*  Class used to map reader properties from the modeler to the object ReaderProperties
*/
class ReaderPropertiesMapper {
	
private:
	/**
	* Hide constructor to create a static class
	*/
	ReaderPropertiesMapper() {};

public:
	/**
	*   Function used to map properties from @dgnElementECInstanceP the modeler to the object @readerProperties
	*   @param dgnElementECInstanceP[in] properties from modeler to be mapped
	*   @param readerProperties[out] modeler properties are maped into this object
	*/
	static void mapECPropertiesToReaderProperties(DgnElementECInstanceP dgnElementECInstanceP, ReaderProperties &readerProperties);


	/**
	*   Function used to map a single property based on the received information from the modeler
	*   @param labelValue[in] name of the property
	*   @param eCValue[in] value of the property
	*   @param readerProperties[out] store property and it's value
	*/
	static void mapPropertyToReaderPropertiesMember(std::string labelValue, ECValue eCValue, ReaderProperties &readerProperties);
};