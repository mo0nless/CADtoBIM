#pragma once

#include "../stdafx.h"
#include "PropertiesDictionary.h"
#include "../utils/ElementPropertiesEnum.cpp"
#include "../utils/GraphicPropertiesEnum.cpp"
#include "../utils/StringUtils.h"

class PropertiesReader
{
public:
	static void GetProperties(ElementHandleCR currentElem, std::ofstream& outfile, std::string& filePath, PropertiesDictionary& propsDictionary);
private:
	PropertiesReader();
};
