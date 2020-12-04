#include "..\headers\DataBaseContext.h"

#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4189)
#pragma warning( disable : 4238)
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
	_logger = Logs::Logger::getLogger();

	string fileName = "mappings.txt";
	//string pathName = "C:/Users/LX5990/source/repos/cadtobim/ParametricFeatures/data_base/mappings.txt";
	string pathName = " ";

	try {
		char path[MAX_PATH];
		HMODULE hm = NULL;

		if (GetModuleHandleEx(GET_MODULE_HANDLE_EX_FLAG_FROM_ADDRESS |
			GET_MODULE_HANDLE_EX_FLAG_UNCHANGED_REFCOUNT,
			(LPCSTR)&DataBaseContext::getComponentsMappingVector(), &hm) == 0)
		{
			int ret = GetLastError();
			fprintf(stderr, "GetModuleHandle failed, error = %d\n", ret);
			// Return or however you want to handle an error.
		}
		if (GetModuleFileName(hm, path, sizeof(path)) == 0)
		{
			int ret = GetLastError();
			fprintf(stderr, "GetModuleFileName failed, error = %d\n", ret);
			// Return or however you want to handle an error.
		}

		string dPath(path);

		pathName = dPath + "\\" + fileName;
	}
	catch (exception& ex) {
		_logger->logFatal(__FILE__, __LINE__, __func__, ex, "Error at initializing the ifcElementBundleVector");
		throw ex;
	}
	
	ifstream infile(pathName);
	
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
