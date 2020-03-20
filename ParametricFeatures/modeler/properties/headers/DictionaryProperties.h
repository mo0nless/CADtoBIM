#pragma once

#include "ReaderProperties.h"
#include "GraphicProperties.h"
#include "GeneralProperties.h"



/**
 *  Class stores ReaderProperties, GraphicProperties and other relevant properties
 */
class DictionaryProperties {

private:
	GeneralProperties* mGeneralProperties;
	ReaderProperties* mReaderProperties;
	GraphicProperties* mGraphicProperties;

	bool areReaderPropertiesFound;

	

public:
	DictionaryProperties();

	GeneralProperties* getGeneralProperties();
	ReaderProperties* getReaderProperties();
	GraphicProperties* getGraphicProperties();
	
	bool getAreReaderPropertiesFound();
	void setAreReaderPropertiesFound(bool newAreReaderPropertiesFound);

};