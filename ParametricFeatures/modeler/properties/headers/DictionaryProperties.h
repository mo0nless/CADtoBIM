#pragma once

#include "ReaderPropertiesBundle.h"
#include "GraphicProperties.h"
#include "../smart_feature/headers/SmartFeatureContainer.h"


/**
 *  Class stores ReaderProperties, GraphicProperties and other relevant properties
 */
class DictionaryProperties {

private:
	long elementId;
	std::string elementName;

	std::vector<ReaderPropertiesBundle*> readerPropertiesBundleVector;
	std::vector<GraphicProperties*> graphicPropertiesVector;

	SmartFeatureContainer * smartFeatureContainer;


public:
	DictionaryProperties(long newElementId, std::string newElementName);

	std::vector<ReaderPropertiesBundle*> getReaderPropertiesBundleVector();
	void addReaderPropertiesBundle(ReaderPropertiesBundle* readerPropertiesBundle);

	std::vector<GraphicProperties*> getGraphicPropertiesVector();
	void addGraphicProperties(GraphicProperties* graphicProperties);

	SmartFeatureContainer* getSmartFeatureContainer();

	std::string getElementName();

};