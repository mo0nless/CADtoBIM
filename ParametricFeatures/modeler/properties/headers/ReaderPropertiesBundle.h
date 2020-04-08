#pragma once

#include<vector>

#include "../reader/headers/ReaderPropertyDefinition.h"


class ReaderPropertiesBundle {

private:
	std::string className;
	int localId;
	std::vector<ReaderPropertyDefinition> properties;

public:
	ReaderPropertiesBundle(std::string newClassName, int newLocalId);

	std::string getCassName();
	int getLocalId();

	std::vector<ReaderPropertyDefinition> getProperties();
	void addProperty(ReaderPropertyDefinition readerPropertyDefinition);

};