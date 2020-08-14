#pragma once


#include "../headers/ElementBundle.h"
#include "../smart_feature/headers/SmartFeatureContainer.h"
#include "../../../headers/SessionManager.h"


/**
 *  Class stores ReaderProperties, GraphicProperties and other relevant properties
 */
class DictionaryProperties {

private:
	long elementId;
	std::string elementDescriptor;

	bool isSmartSolid;
	bool isPrimitiveSolid;

	//std::vector<ReaderPropertiesBundle*> graphicsReaderPropertiesBundleVector;
	//std::vector<GraphicProperties*> graphicPropertiesVector;

	std::vector<ReaderPropertiesBundle*> elementReaderPropertiesBundleVector;

	SmartFeatureContainer * smartFeatureContainer;

	std::vector<ElementBundle*> subElements;
	

public:
	DictionaryProperties(long newElementId, std::string newEmentDescriptor);

	/*std::vector<ReaderPropertiesBundle*> getGraphicsReaderPropertiesBundleVector();
	void addGraphicsReaderPropertiesBundle(ReaderPropertiesBundle* readerPropertiesBundle);

	std::vector<GraphicProperties*> getGraphicPropertiesVector();
	void addGraphicProperties(GraphicProperties* graphicProperties);*/

	std::vector<ElementBundle*> getElementBundle();
	void addElementBundle(ElementBundle* elementBundle);

	std::vector<ReaderPropertiesBundle*> getElementReaderPropertiesBundleVector();
	void addElementReaderPropertiesBundle(ReaderPropertiesBundle* readerPropertiesBundle);


	void setSmartFeatureContainer(SmartFeatureContainer* newSmartFeatureContainer);
	SmartFeatureContainer* getSmartFeatureContainer();

	std::string getElementDescriptor();

	long getElementId();

	void setIsSmartSolid(bool value);
	bool getIsSmartSolid();

	void setIsPrimitiveSolid(bool value);
	bool getIsPrimitiveSolid();
};