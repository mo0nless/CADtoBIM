#include "..\headers\DataBaseContext.h"


DataBaseContext *DataBaseContext::_dataBaseContext = 0;


DataBaseContext::DataBaseContext()
{
	//sqlite3 *db;
	//char *zErrMsg = 0;
	//int rc;

	//rc = sqlite3_open("C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/data_base/database.db", &db);

	//if (rc) {
	//	fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
	//	return(0);
	//}
	//else {
	//	fprintf(stderr, "Opened database successfully\n");
	//}
	//sqlite3_close(db);
	
	ifstream infile("C:/Users/LX5990/source/repos/cadtobim/ParametricFeatures/data_base/mappings.txt");
	
	string delimiter = ":";
	string lineString, modelerComponent, ifcComponent;

	while (infile >> lineString)
	{
		//modelerComponent = lineString.substr(0, lineString.find(delimiter));
		//ifcComponent = lineString.substr(lineString.find(delimiter) + 1, lineString.length());

		//ComponentsMapping* componentsMapping = new ComponentsMapping();
		//componentsMapping->setModelerComponentName(modelerComponent);
		//componentsMapping->setIfcComponentName(ifcComponent);

		//_componentsMappingVector.push_back(componentsMapping);

		vector<string> results;

		stringstream  ss(lineString);
		string str;
		while (getline(ss, str, ':')) {
			results.push_back(str);
		}

		ComponentsMapping* componentsMapping = new ComponentsMapping();

		if (results.size() == 3) {
			componentsMapping->setModelerComponentName(results[0]);
			componentsMapping->setIfcComponentTypeName(results[1]);
			componentsMapping->setIfcComponentName(results[2]);

		}
		_componentsMappingVector.push_back(componentsMapping);

	}
}

vector<ComponentsMapping*> DataBaseContext::getComponentsMappingVector()
{
	return this->_componentsMappingVector;
}
