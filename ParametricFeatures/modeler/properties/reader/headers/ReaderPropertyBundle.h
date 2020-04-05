#pragma once

#include<vector>

#include "ReaderPropertyDefinition.h"


class ReaderPropertyBundle {

private:
	std::string className;
	int localId;
	std::vector<ReaderPropertyDefinition> properties;

public:
	ReaderPropertyBundle(std::string newClassName,int newLocalId);

	std::string getCassName();
	int getLocalId();

	std::vector<ReaderPropertyDefinition> getProperties();
	void addProperty(ReaderPropertyDefinition readerPropertyDefinition);

};