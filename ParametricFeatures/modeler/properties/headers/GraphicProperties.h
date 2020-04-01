#pragma once

#include "../primitives/graphic/headers/PrimitiveGraphicProperties.h"
#include "../curves/graphic/headers/CurveGraphicProperties.h"

/**
 *   Class contains needed graphic properties
 */
class GraphicProperties {

private:
	std::vector<PrimitiveGraphicProperties*> primitiveGraphicPropertiesVector;
	CurveGraphicProperties* pCurveGraphicProperties;

public:
	GraphicProperties();

	bool tryGetCurveGraphicsProperties(CurveGraphicProperties*& curveGraphicsPropertiesR);
	void setCurveGraphicsProperties(CurveGraphicProperties* newCurveGraphicsProperties);

	void addPrimitiveGraphicProperties(PrimitiveGraphicProperties* newPrimitiveGraphicProperties);
	std::vector<PrimitiveGraphicProperties*> getPrimitiveGraphicPropertiesVector();
};