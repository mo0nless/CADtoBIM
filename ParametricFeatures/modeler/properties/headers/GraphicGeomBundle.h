#pragma once

#include "../reader/headers/ReaderPropertiesBundle.h"
#include "GraphicProperties.h"
#include <fstream>
#include <DgnPlatform\ColorUtil.h>

using namespace std;

class GraphicGeomBundle {

private:
	GraphicProperties* graphicProperties;
	vector<ReaderPropertiesBundle*> readerPropertiesBundleVector;

	ElementHandle elementHandle;

	UInt32 _color;
	double _transparency;
	string _material;
	LevelHandle _levelID;
	IntColorDef lineColorDef;
	RgbFactor fillColorDef;

public:

	ElementHandle getElementHandle();
	void setElementHandle(ElementHandle newElementHandle);

	GraphicProperties* getGraphicProperties();
	void setGraphicProperties(GraphicProperties& newGraphicProperties);

	vector<ReaderPropertiesBundle*> getReaderPropertiesBundleVector();
	void addReaderPropertiesBundle(ReaderPropertiesBundle* newReaderPropertiesBundle);
	void setReaderPropertiesBundle(vector<ReaderPropertiesBundle*> newReaderPropertiesBundleVector);

	UInt32 getColor();
	void setColor(UInt32 newColor);

	RgbFactor getFillColor();
	void setFillColor(RgbFactor newColor);

	IntColorDef getLineColor();
	void setLineColor(IntColorDef newColor);

	LevelHandle getLevelHandle();
	void setLevelHandle(LevelHandle level);
	
	double getTransparency();
	void setTransparency(double newTransparency);

	string getMaterial();
	void setMaterial(string material);

	string toString();
};