#pragma once
#include <string>

using namespace std;

namespace DataBase
{
	namespace Models
	{
		class ComponentsMapping {

		private:
			int _id;

			string _modelerComponentName;
			string _ifcTypeComponentName;
			string _ifcComponentName;

		public:
			string getModelerComponentName();
			void setModelerComponentName(string modelerComponentName);

			string getIfcComponentName();
			void setIfcComponentName(string ifcComponentName);

			string getIfcComponentTypeName();
			void setIfcComponentTypeName(string ifcComponentTypeName);
		};
	}
}