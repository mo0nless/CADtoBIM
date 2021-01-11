#pragma once

#include "../../../stdafx.h"

#include "../../main/headers/IfcElementBundle.h"
#include "../../../common/utils/headers/StringUtils.hpp"
#include "../../../common/utils/headers/NumberUtils.h"
#include "../../../common/utils/headers/PropertyTypeEnumUtils.h"

using namespace Ifc::Main;

class IfcPropertiesEnhancer {

public:
	void enhance(vector<IfcElementBundle*>& ifcElementBundleVector, IfcHierarchyHelper<Ifc4>& file, Ifc4::IfcOwnerHistory* ownerHistory);

private:
	Logs::Logger* _logger = Logs::Logger::getLogger();

	Ifc4::IfcOwnerHistory* _ownerHistory;

	Ifc4::IfcPropertySet* createIfcPropertySet(ReaderPropertiesBundle& readerPropertiesBundle, IfcHierarchyHelper<Ifc4>& file);
	Ifc4::IfcProperty* createIfcBasicProperty(ReaderPropertyDefinition& readerPropertyDefinition);
	Ifc4::IfcProperty* createIfcComplexProperty(ReaderPropertyDefinition& readerPropertyDefinition);
};