#pragma once

#include<vector>

#include "ReaderPropertyDefinition.h"

using namespace std;

class ReaderPropertiesBundle {

private:
	string className;
	int localId;
	string _name;
	vector<ReaderPropertyDefinition*> properties;

public:
	ReaderPropertiesBundle(string newClassName, int newLocalId);

	string getClassName();
	int getLocalId();
	void setLocalId(int newLocalId);

	string getName();
	void setName(string name);


	vector<ReaderPropertyDefinition*> getProperties();
	void addProperty(ReaderPropertyDefinition* readerPropertyDefinition);

};