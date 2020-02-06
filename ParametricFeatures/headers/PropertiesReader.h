#pragma once

#include "PropertiesDictionary.h"
#include "../utils/TypesUtils.h"
#include "../utils/StringUtils.h"

class PropertiesReader
{
public:
	PropertiesReader(ElementHandleCR currentElem, std::ofstream& outfile, std::string& filePath, PropertiesDictionary& propsDictionary);
	std::string getElemClassName();
private:
	std::string elemClassName;
	PropertiesReader();
};
