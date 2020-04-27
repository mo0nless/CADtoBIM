#pragma once

#include "../../../stdafx.h"
#include "../../../modeler/properties/headers/DictionaryProperties.h"
#include "../../headers/IfcElementBundle.h"
#include "../../../common/utils/headers/StringUtils.hpp"
#include "../../../common/utils/headers/NumberUtils.h"
#include "../../../common/utils/headers/PropertyTypeEnumUtils.h"

class IfcMaterialEnhancer {

public:
	void enhanceMaterials(std::vector<DictionaryProperties*>& dictionaryPropertiesVector, std::vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file);

private:
	void processMaterials(ReaderPropertiesBundle& readerPropertiesBundle, IfcHierarchyHelper<Ifc4>& file, IfcElementBundle& ifcElementBundle);
	void processColour(ReaderPropertyDefinition& readerPropertyDefinition, IfcHierarchyHelper<Ifc4>& file, IfcElementBundle& ifcElementBundle);
	void processMaterial(ReaderPropertyDefinition& readerPropertyDefinition, IfcHierarchyHelper<Ifc4>& file, Ifc4::IfcElement* ifcElement);

	Ifc4::IfcColourRgb* parseAndCreateColour(std::string colourValue);
};