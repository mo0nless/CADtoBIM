#pragma once

#include "../../../stdafx.h"
#include "../../../data_processing/modeler/properties/reader/headers/ReaderPropertiesBundle.h"

namespace Ifc
{
	namespace Bundle
	{
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
	}
}