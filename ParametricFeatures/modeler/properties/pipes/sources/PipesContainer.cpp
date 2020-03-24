#include "../headers/PipesContainer.h"

PipesContainer::PipesContainer()
{
	this->generalProperties = new GeneralProperties();
	this->readerProperties = new ReaderProperties();
	this->graphicProperties = new GraphicProperties();
}

GeneralProperties * PipesContainer::getGeneralProperties()
{
	return this->generalProperties;
}

ReaderProperties * PipesContainer::getReaderProperties()
{
	return this->readerProperties;
}

GraphicProperties * PipesContainer::getGraphicProperties()
{
	return this->graphicProperties;
}

void PipesContainer::setGraphicProperties(GraphicProperties * newGraphicProperties)
{
	this->graphicProperties = newGraphicProperties;
}
