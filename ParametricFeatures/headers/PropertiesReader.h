#pragma once

#include "../stdafx.h"
#include "PropertiesDictionary.h"
#include "../utils/ElementPropertiesEnum.cpp"
#include "../utils/GraphicPropertiesEnum.cpp"
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
