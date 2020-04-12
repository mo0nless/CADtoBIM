#pragma once

#include "../../../stdafx.h"
#include "../../../modeler/properties/headers/DictionaryProperties.h"
#include "../../headers/IfcBundle.h"
#include "../../../common/utils/headers/StringUtils.hpp"
#include "../../../common/utils/headers/NumberUtils.h"
#include "../../../common/utils/headers/PropertyTypeEnumUtils.h"

class IfcPropertiesEnhancer {

public:
	void enhanceIfcProperties(std::vector<DictionaryProperties*>& dictionaryPropertiesVector, std::vector<IfcBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file);

private:
	Ifc4::IfcPropertySet* createIfcPropertySet(ReaderPropertiesBundle& readerPropertiesBundle, IfcHierarchyHelper<Ifc4>& file);
	Ifc4::IfcProperty* createIfcBasicProperty(ReaderPropertyDefinition& readerPropertyDefinition);
	Ifc4::IfcProperty* createIfcComplexProperty(ReaderPropertyDefinition& readerPropertyDefinition);
};