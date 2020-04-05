#include "../headers/GraphicProperties.h"

GraphicProperties::GraphicProperties()
{
	this->pCurveGraphicProperties = nullptr;
}


bool GraphicProperties::tryGetCurvesPrimitivesContainer(CurvesPrimitivesContainer*& curvesPrimitivesContainersR)
{
	if (this->pCurvesPrimitivesContainer == nullptr)
	{
		return false;
	}
	curvesPrimitivesContainersR = this->pCurvesPrimitivesContainer;
	return true;
}

void GraphicProperties::setCurvesPrimitivesContainer(CurvesPrimitivesContainer* newCurvesPrimitivesContainer)
{
	this->pCurvesPrimitivesContainer = newCurvesPrimitivesContainer;
}

void GraphicProperties::addPrimitiveGraphicProperties(PrimitiveGraphicProperties * newPrimitiveGraphicProperties)
{
	this->primitiveGraphicPropertiesVector.push_back(newPrimitiveGraphicProperties);
}

std::vector<PrimitiveGraphicProperties*> GraphicProperties::getPrimitiveGraphicPropertiesVector()
{
	return this->primitiveGraphicPropertiesVector;
}

