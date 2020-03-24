#pragma once

#include "../../../properties/headers/GeneralProperties.h"
#include "../../../properties/headers/ReaderProperties.h"
#include "../../../properties/headers/GraphicProperties.h"

class PipesContainer {

private:
	GeneralProperties* generalProperties;
	ReaderProperties* readerProperties;
	GraphicProperties* graphicProperties;


public:
	PipesContainer();

	GeneralProperties* getGeneralProperties();
	ReaderProperties* getReaderProperties();

	GraphicProperties* getGraphicProperties();
	void setGraphicProperties(GraphicProperties* newGraphicProperties);

};