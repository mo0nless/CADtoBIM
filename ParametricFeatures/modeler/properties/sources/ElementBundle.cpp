#include "../headers/ElementBundle.h"

ElementHandle ElementBundle::getElementHandle()
{
	return this->elementHandle;
}

void ElementBundle::setElementHandle(ElementHandle newElementHandle)
{
	this->elementHandle = newElementHandle;
}

GraphicProperties * ElementBundle::getGraphicProperties()
{
	return this->graphicProperties;
}

void ElementBundle::setGraphicProperties(GraphicProperties & newGraphicProperties)
{
	this->graphicProperties = &newGraphicProperties;
}

ReaderPropertiesBundle * ElementBundle::getReaderPropertiesBundle()
{
	return this->readerPropertiesBundle;
}

void ElementBundle::setReaderPropertiesBundle(ReaderPropertiesBundle & newReaderPropertiesBundle)
{
	this->readerPropertiesBundle = &newReaderPropertiesBundle;
}

ElemDisplayParamsCP ElementBundle::getElemDisplayParamsCP()
{
	return this->elemDisplayParamsCP;
}

void ElementBundle::setElemDisplayParamsCR(ElemDisplayParamsCR newElemDisplayParamsCR)
{
	this->elemDisplayParamsCP =  ElemDisplayParamsCP(&newElemDisplayParamsCR);

	/*std::string filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
	std::ofstream outfile;
	outfile.open(filePath, std::ios_base::app);

	UInt32 color2;

	color2 = elemDisplayParamsCP->GetLineColorTBGR();
	int blue1 = (color2 >> 16) & 0xFF;
	int green1 = (color2 >> 8) & 0xFF;
	int red1 = color2 & 0xFF;
	outfile << "setElemDisplayParamsCR" << std::endl;
	outfile << "RGB =" << red1 << "," << green1 << "," << blue1 << std::endl;
	outfile.close();*/
}

UInt32 ElementBundle::getColor()
{
	return this->color;
}

void ElementBundle::setColor(UInt32 newColor)
{
	this->color = newColor;
}

double ElementBundle::getTransparency()
{
	return this->transparency;
}

void ElementBundle::setTransparency(double newTransparency)
{
	this->transparency = newTransparency;
}

std::string ElementBundle::getMaterial()
{
	return this->_material;
}

void ElementBundle::setMaterial(std::string material)
{
	this->_material = material;
}
