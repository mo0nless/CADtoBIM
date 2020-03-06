#pragma once

#include "ReaderProperties.h"
#include "GraphicProperties.h"
#include "GeneralProperties.h"

/**
 *  Class stores ReaderProperties, GraphicProperties and other relevant properties
 */
class DictionaryProperties {

private:
	GeneralProperties* generalProperties;
	ReaderProperties* readerProperties;
	GraphicProperties* graphicProperties;

	bool areReaderPropertiesFound;
	

public:
	DictionaryProperties();
	~DictionaryProperties();

	GeneralProperties* getGeneralProperties();
	ReaderProperties* getReaderProperties();
	GraphicProperties* getGraphicProperties();
	
	bool getIsSmartFeatureMissingReaderProperties();
	void setIsSmartFeatureMissingReaderProperties(bool newAreReaderPropertiesFound);

};