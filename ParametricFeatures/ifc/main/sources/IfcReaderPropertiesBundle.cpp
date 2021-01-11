#include "../headers/IfcReaderPropertiesBundle.h"

using namespace Ifc::Main;

IfcReaderPropertiesBundle::IfcReaderPropertiesBundle(ReaderPropertiesBundle * newReaderPropertiesBundle)
{
	this->readerPropertiesBundle = newReaderPropertiesBundle;
}

void IfcReaderPropertiesBundle::setIfcPropertySet(Ifc4::IfcPropertySet * ifcPropertySetValue)
{
	this->ifcPropertySet = ifcPropertySetValue;
}

ReaderPropertiesBundle * IfcReaderPropertiesBundle::getReaderPropertiesBundle()
{
	return this->readerPropertiesBundle;
}

Ifc4::IfcPropertySet * IfcReaderPropertiesBundle::getIfcPropertySet()
{
	return this->ifcPropertySet;
}
