#pragma once
#include <string>

using namespace std;

class ComponentsMapping {

private:
	int _id;

	string _modelerComponentName;
	string _ifcComponentName;

public:
	string getModelerComponentName();
	void setModelerComponentName(string modelerComponentName);

	string getIfcComponentName();
	void setIfcComponentName(string ifcComponentName);
};