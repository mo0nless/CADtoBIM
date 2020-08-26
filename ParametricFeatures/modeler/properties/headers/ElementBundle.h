#pragma once

#include "../reader/headers/ReaderPropertiesBundle.h"
#include "GraphicProperties.h"
#include <fstream>

class ElementBundle {

private:
	GraphicProperties* graphicProperties;
	ReaderPropertiesBundle* readerPropertiesBundle;

	ElementHandle elementHandle;
	ElemDisplayParamsCP elemDisplayParamsCP;

	UInt32 color;
	double transparency;
	std::string _material;

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

	std::string getMaterial();
	void setMaterial(std::string material);

};