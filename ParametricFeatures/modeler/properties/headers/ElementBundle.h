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
	ElemDisplayParamsCP elemDisplayParamsCP;

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


	ElemDisplayParamsCP getElemDisplayParamsCP();
	void setElemDisplayParamsCR(ElemDisplayParamsCR newElemDisplayParamsCR);

	UInt32 getColor();
	void setColor(UInt32 newColor);
	
	double getTransparency();
	void setTransparency(double newTransparency);

	string getMaterial();
	void setMaterial(string material);

};