#include "..\headers\DataBaseContext.h"


DataBaseContext *DataBaseContext::_dataBaseContext = 0;


DataBaseContext::DataBaseContext()
{
	ifstream infile("C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/data_base/mappings.txt");
	string delimiter = ":";
	string lineString, modelerComponent, ifcComponent;

	while (infile >> lineString)
	{
		modelerComponent = lineString.substr(0, lineString.find(delimiter));
		ifcComponent = lineString.substr(lineString.find(delimiter) + 1, lineString.length());

		ComponentsMapping* componentsMapping = new ComponentsMapping();
		componentsMapping->setModelerComponentName(modelerComponent);
		componentsMapping->setIfcComponentName(ifcComponent);

		_componentsMappingVector.push_back(componentsMapping);

	}
}

vector<ComponentsMapping*> DataBaseContext::getComponentsMappingVector()
{
	return this->_componentsMappingVector;
}
