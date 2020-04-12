#include "../headers/IfcReaderPropertiesBundle.h"

IfcReaderPropertiesBundle::IfcReaderPropertiesBundle(ReaderPropertiesBundle * newReaderPropertiesBundle, Ifc4::IfcPropertySet * newIfcPropertySet)
{
	this->readerPropertiesBundle;
	this->ifcPropertySet = newIfcPropertySet;
}

ReaderPropertiesBundle * IfcReaderPropertiesBundle::getReaderPropertiesBundle()
{
	return this->readerPropertiesBundle;
}

Ifc4::IfcPropertySet * IfcReaderPropertiesBundle::getIfcPropertySet()
{
	return this->ifcPropertySet;
}
