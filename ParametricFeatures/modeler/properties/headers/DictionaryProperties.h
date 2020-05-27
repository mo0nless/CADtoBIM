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
	std::string elementDescriptor;

	bool isSmartSolid;
	bool isPrimitiveSolid;

	std::vector<ReaderPropertiesBundle*> readerPropertiesBundleVector;
	std::vector<GraphicProperties*> graphicPropertiesVector;

	SmartFeatureContainer * smartFeatureContainer;

public:
	DictionaryProperties(long newElementId, std::string newEmentDescriptor);

	std::vector<ReaderPropertiesBundle*> getReaderPropertiesBundleVector();
	void addReaderPropertiesBundle(ReaderPropertiesBundle* readerPropertiesBundle);

	std::vector<GraphicProperties*> getGraphicPropertiesVector();
	void addGraphicProperties(GraphicProperties* graphicProperties);

	void setSmartFeatureContainer(SmartFeatureContainer* newSmartFeatureContainer);
	SmartFeatureContainer* getSmartFeatureContainer();

	std::string getElementDescriptor();

	long getElementId();

	void setIsSmartSolid(bool value);
	bool getIsSmartSolid();

	void setIsPrimitiveSolid(bool value);
	bool getIsPrimitiveSolid();
};