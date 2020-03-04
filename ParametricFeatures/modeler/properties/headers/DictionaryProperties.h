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
	bool isSmartFeature;
	

public:
	DictionaryProperties();

	GeneralProperties* getGeneralProperties();
	ReaderProperties* getReaderProperties();
	GraphicProperties* getGraphicProperties();

	bool getIsSmartFeature();
	void setIsSmartFeature(bool newIsSmartFeature);

	bool getSmartFeatureMissingReaderProperties();
	void setSmartFeatureMissingReaderProperties(bool newAreReaderPropertiesFound);

};