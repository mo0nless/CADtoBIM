#pragma once

#include<vector>

#include "ReaderPropertyDefinition.h"

using namespace std;

class ReaderPropertiesBundle {

private:
	string className;
	int localId;
	vector<ReaderPropertyDefinition*> properties;

public:
	ReaderPropertiesBundle(string newClassName, int newLocalId);

	string getCassName();
	int getLocalId();

	vector<ReaderPropertyDefinition*> getProperties();
	void addProperty(ReaderPropertyDefinition* readerPropertyDefinition);

};