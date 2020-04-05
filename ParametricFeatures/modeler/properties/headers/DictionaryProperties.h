#pragma once

#include "ReaderProperties.h"
#include "GraphicProperties.h"
#include "GeneralProperties.h"
#include "../smart_feature/headers/SmartFeatureContainer.h"


/**
 *  Class stores ReaderProperties, GraphicProperties and other relevant properties
 */
class DictionaryProperties {

private:
	long elementId;
	std::string elementName;

	ReaderProperties* pReaderProperties;
	GraphicProperties* pGraphicProperties;
	SmartFeatureContainer * smartFeatureContainer;


public:
	DictionaryProperties(long newElementId, std::string newElementName);

	ReaderProperties* getReaderProperties();
	GraphicProperties* getGraphicProperties();
	SmartFeatureContainer* getSmartFeatureContainer();

	std::string getElementName();

};