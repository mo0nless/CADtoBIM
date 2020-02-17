#pragma once


#include<string>
#include<map>

#include "../../headers/ReaderProperties.h"
#include "../../headers/GraphicProperties.h"
#include <vector>

class SmartFeatureProperties
{
private:
	ReaderProperties* readerProperties;
	GraphicProperties* graphicProperties;

	std::string className;
	long elementId;
	long currentElementId;

	long localNodeId;
	long localParentNodeId;

public:
	SmartFeatureProperties();

	std::string getClassName();
	void setClassName(std::string newClassName);

	long getElementId();
	void setElementId(long newElementId);

	long getCurrentElementId();
	void setCurrentElementId(long newCurrentElementId);

	long getLocalNodeId();
	void setLocalNodeId(long newLocalNodeId);

	long getLocalParentNodeId();
	void setLocalParentNodeId(long newLocalParentNodeId);

	ReaderProperties* getReaderProperties();
	void setReaderProperties(ReaderProperties* newReaderProperties);

	GraphicProperties* getGraphicProperties();
	void setGraphicProperties(GraphicProperties* newGraphicProperties);

};