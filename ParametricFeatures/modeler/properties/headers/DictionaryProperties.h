#pragma once

#include "ReaderProperties.h"
#include "GraphicProperty.h"
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
	std::vector<GraphicProperty*> graphicProperties;
	//GraphicProperties* pGraphicProperties;
	SmartFeatureContainer * smartFeatureContainer;


public:
	DictionaryProperties(long newElementId, std::string newElementName);

	ReaderProperties* getReaderProperties();

	std::vector<GraphicProperty*> getGraphicProperties();
	void addGraphicProperty(GraphicProperty* graphicProperty);

	//GraphicProperties* getGraphicProperties();
	SmartFeatureContainer* getSmartFeatureContainer();

	std::string getElementName();

};