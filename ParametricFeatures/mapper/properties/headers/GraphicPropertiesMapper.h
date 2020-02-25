#pragma once

#include <Bentley/WString.h>

#include <DgnPlatform/DgnECInstance.h>
#include <DgnPlatform/DgnECManager.h>

USING_NAMESPACE_BENTLEY_ECOBJECT;
USING_NAMESPACE_BENTLEY_DGNPLATFORM;

#include "../../../common/utils/StringUtils.hpp"
//#include "../../../common/enums/headers/PrimitiveTypeEnum.h"

#include "../../../modeler/properties/headers/GraphicProperties.h"

#define _USE_MATH_DEFINES
#include <math.h>


/**
 *  Class used to map grapich properties from the modeler to the object GraphicProperties
 */
class GraphicPropertiesMapper {

private:
	/**
	 * Hide constructor to create a static class
	 */
	GraphicPropertiesMapper() {};

public:

	/**
	 *   Function used to map properties from @primitive the modeler to the object @graphicProperties
	 *   @param primitive[in] properties from modeler to be mapped
	 *   @param graphicProperties[out] modeler properties are maped into this object
	 */
	static void mapPrincipalMomentsToGraphicProperties(ISolidPrimitiveCR& primitive, GraphicProperties &graphicProperties);
};