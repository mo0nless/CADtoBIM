//#pragma once

#include "../../../modeler/properties/headers/DictionaryProperties.h"

#include <ifcparse\IfcSchema.h>
#include <ifcparse\Ifc4.h>
#include <ifcparse\utils.h>
#include <ifcparse\IfcHierarchyHelper.h>

//#include "../../../stdafx.h"

class PrimitivesMapperHandler {

private:
	PrimitivesMapperHandler() {};

public:
	static void buildPrimitive(DictionaryProperties& dictionaryProperties);
};