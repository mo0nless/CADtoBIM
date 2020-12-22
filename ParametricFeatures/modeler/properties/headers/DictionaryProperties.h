#pragma once


//#include "../headers/GraphicGeomBundle.h"
#include "../../../ifc/main/headers/IfcGraphicPropertiesBundle.h"
#include "../../../modeler/properties/reader/headers/ReaderPropertiesBundle.h"
#include "../smart_feature/headers/SmartFeatureContainer.h"
#include "../../../common/models/headers/SessionManager.h"

using namespace std;

/**
 *  Class stores ReaderProperties, GraphicProperties and other relevant properties
 */
class DictionaryProperties {

private:
	long elementId;
	string elementDescriptor;

	bool isSmartSolid;
	bool isPrimitiveSolid;

	vector<ReaderPropertiesBundle*> elementReaderPropertiesBundleVector;

	SmartFeatureContainer * smartFeatureContainer;

	vector<IfcGraphicPropertiesBundle*> subElements;
	string mElemClassName;
public:
	DictionaryProperties(long newElementId, string newElementDescriptor);

	string getElementClassName();
	void setElementClassName(string name);

	vector<IfcGraphicPropertiesBundle*> getIfcGraphicPropertiesBundleVector();
	void addGraphicGeomBundle(IfcGraphicPropertiesBundle* elementBundle);

	vector<ReaderPropertiesBundle*> getElementReaderPropertiesBundleVector();
	void setElementReaderPropertiesBundleVector(vector<ReaderPropertiesBundle*> newReaderPropertiesBundleVector);
	void addElementReaderPropertiesBundle(ReaderPropertiesBundle* readerPropertiesBundle);


	void setSmartFeatureContainer(SmartFeatureContainer* newSmartFeatureContainer);
	SmartFeatureContainer* getSmartFeatureContainer();

	string getElementDescriptor();

	long getElementId();

	void setIsSmartSolid(bool value);
	bool getIsSmartSolid();

	void setIsPrimitiveSolid(bool value);
	bool getIsPrimitiveSolid();

	string toString();
};