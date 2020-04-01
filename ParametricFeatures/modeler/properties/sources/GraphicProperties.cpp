#include "../headers/GraphicProperties.h"

GraphicProperties::GraphicProperties()
{
	this->pCurveGraphicProperties = nullptr;
}


bool GraphicProperties::tryGetCurveGraphicsProperties(CurveGraphicProperties*& curveGraphicsPropertiesR)
{
	if (this->pCurveGraphicProperties == nullptr)
	{
		return false;
	}
	curveGraphicsPropertiesR = this->pCurveGraphicProperties;
	return true;
}

void GraphicProperties::setCurveGraphicsProperties(CurveGraphicProperties * newCurveGraphicsProperties)
{
	this->pCurveGraphicProperties = newCurveGraphicsProperties;
}

void GraphicProperties::addPrimitiveGraphicProperties(PrimitiveGraphicProperties * newPrimitiveGraphicProperties)
{
	this->primitiveGraphicPropertiesVector.push_back(newPrimitiveGraphicProperties);
}

std::vector<PrimitiveGraphicProperties*> GraphicProperties::getPrimitiveGraphicPropertiesVector()
{
	return this->primitiveGraphicPropertiesVector;
}

