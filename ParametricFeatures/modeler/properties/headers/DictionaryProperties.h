#pragma once

#include "ReaderProperties.h"
#include "GraphicProperties.h"

/**
 *  Class stores ReaderProperties, GraphicProperties and other relevant properties
 */
class DictionaryProperties {

private:
	ReaderProperties* readerProperties;
	GraphicProperties* graphicProperties;

	bool areReaderPropertiesFound;
	bool isSmartFeature;
	std::string className;

public:
	DictionaryProperties();

	ReaderProperties* getReaderProperties();
	GraphicProperties* getGraphicProperties();

	bool getIsSmartFeature();
	void setIsSmartFeature(bool newIsSmartFeature);

	std::string getClassName();
	void setClassName(std::string newClassName);

	bool getAreReaderPropertiesFound();
	void setAreReaderPropertiesFound(bool newAreReaderPropertiesFound);

};