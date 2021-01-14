#pragma once

#include <string>
#include <vector>

using namespace std;

namespace DataBase
{
	namespace DTOs
	{
		class ComponentsMappingDTO {
		private:
			int _id;

			string _modelerComponentName;
			string _ifcComponentName;
			string _ifcTypeComponentName;

		public:
			ComponentsMappingDTO();

			string getModelerComponentName();
			void setModelerComponentName(string modelerComponentName);

			string getIfcComponentName();
			void setIfcComponentName(string ifcComponentName);

			string getIfcComponentTypeName();
			void setIfcComponentTypeName(string ifcComponentTypeName);
		};
	}
}