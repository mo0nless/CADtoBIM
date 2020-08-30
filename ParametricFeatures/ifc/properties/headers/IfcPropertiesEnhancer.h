#pragma once

#include "../../../stdafx.h"
#include "../../../modeler/properties/headers/DictionaryProperties.h"
#include "../../main/headers/IfcElementBundle.h"
#include "../../../common/utils/headers/StringUtils.hpp"
#include "../../../common/utils/headers/NumberUtils.h"
#include "../../../common/utils/headers/PropertyTypeEnumUtils.h"

class IfcPropertiesEnhancer {

public:
	void enhanceIfcProperties(vector<DictionaryProperties*>& dictionaryPropertiesVector, vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file);

private:
	Ifc4::IfcPropertySet* createIfcPropertySet(ReaderPropertiesBundle& readerPropertiesBundle, IfcHierarchyHelper<Ifc4>& file);
	Ifc4::IfcProperty* createIfcBasicProperty(ReaderPropertyDefinition& readerPropertyDefinition);
	Ifc4::IfcProperty* createIfcComplexProperty(ReaderPropertyDefinition& readerPropertyDefinition);
};