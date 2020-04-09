#pragma once

#include "../../stdafx.h"
#include "../../modeler/properties/headers/ReaderPropertiesBundle.h"

class IfcReaderPropertiesBundle {

private:
	ReaderPropertiesBundle* readerPropertiesBundle;
	Ifc4::IfcPropertySet* ifcPropertySet;

public:
	IfcReaderPropertiesBundle(ReaderPropertiesBundle* newReaderPropertiesBundle,Ifc4::IfcPropertySet* newIfcPropertySet);

	ReaderPropertiesBundle* getReaderPropertiesBundle();
	Ifc4::IfcPropertySet* getIfcPropertySet();
};