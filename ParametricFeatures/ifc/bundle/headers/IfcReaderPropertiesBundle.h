#pragma once

#include<vector>
#include "../../../stdafx.h"
#include "../../../modeler/properties/reader/headers/ReaderPropertyDefinition.h"

using namespace std;
using namespace Modeler::Properties;

namespace Ifc
{
	namespace Bundle
	{
		class IfcReaderPropertiesBundle {

		private:
			string className;
			int localId;
			string _name;
			vector<ReaderPropertyDefinition*> properties;
			Ifc4::IfcPropertySet* ifcPropertySet;

		public:
			IfcReaderPropertiesBundle(string newClassName, int newLocalId);

			string getClassName();
			int getLocalId();
			void setLocalId(int newLocalId);

			string getName();
			void setName(string name);

			vector<ReaderPropertyDefinition*> getProperties();
			void addProperty(ReaderPropertyDefinition* readerPropertyDefinition);

			void setIfcPropertySet(Ifc4::IfcPropertySet* ifcPropertySetValue);
			Ifc4::IfcPropertySet* getIfcPropertySet();

		};
	}
}