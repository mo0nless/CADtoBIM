#pragma once

#include "../primitives/graphic/headers/PrimitiveGraphicProperties.h"
#include "../curves/headers/CurvesPrimitivesContainer.h"

/**
 *   Class contains needed graphic properties
 */
class GraphicProperties {

private:
	std::vector<PrimitiveGraphicProperties*> primitiveGraphicPropertiesVector;
	CurvesPrimitivesContainer* pCurvesPrimitivesContainer;

public:
	GraphicProperties();

	bool tryGetCurvesPrimitivesContainer(CurvesPrimitivesContainer*& curvesPrimitivesContainersR);
	void setCurvesPrimitivesContainer(CurvesPrimitivesContainer* newCurvesPrimitivesContainer);

	void addPrimitiveGraphicProperties(PrimitiveGraphicProperties* newPrimitiveGraphicProperties);
	std::vector<PrimitiveGraphicProperties*> getPrimitiveGraphicPropertiesVector();
};