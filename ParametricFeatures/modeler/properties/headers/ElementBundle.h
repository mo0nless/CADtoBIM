#pragma once

#include "../reader/headers/ReaderPropertiesBundle.h"
#include "GraphicProperties.h"
#include <fstream>

using namespace std;

class ElementBundle {

private:
	GraphicProperties* graphicProperties;
	ReaderPropertiesBundle* readerPropertiesBundle;

	ElementHandle elementHandle;

	UInt32 color;
	double transparency;
	string _material;

public:

	ElementHandle getElementHandle();
	void setElementHandle(ElementHandle newElementHandle);

	GraphicProperties* getGraphicProperties();
	void setGraphicProperties(GraphicProperties& newGraphicProperties);

	ReaderPropertiesBundle* getReaderPropertiesBundle();
	void setReaderPropertiesBundle(ReaderPropertiesBundle& newReaderPropertiesBundle);

	UInt32 getColor();
	void setColor(UInt32 newColor);
	
	double getTransparency();
	void setTransparency(double newTransparency);

	string getMaterial();
	void setMaterial(string material);

};