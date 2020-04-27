#pragma once

#include "../../stdafx.h"
#include "../../modeler/properties/headers/ReaderPropertiesBundle.h"

class IfcReaderPropertiesBundle {

private:
	ReaderPropertiesBundle* readerPropertiesBundle;
	Ifc4::IfcPropertySet* ifcPropertySet;

public:
	IfcReaderPropertiesBundle(ReaderPropertiesBundle* newReaderPropertiesBundle);

	void setIfcPropertySet(Ifc4::IfcPropertySet* ifcPropertySetValue);
	ReaderPropertiesBundle* getReaderPropertiesBundle();
	Ifc4::IfcPropertySet* getIfcPropertySet();
};