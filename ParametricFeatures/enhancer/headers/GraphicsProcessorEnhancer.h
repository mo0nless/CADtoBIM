#pragma once

#include "../../headers/PropertiesReaderProcessor.h"
#include "../../modeler/properties/primitives/graphic/headers/PrimitiveGraphicProperties.h"
#include "../../modeler/properties/curves/headers/CurvesPrimitivesContainer.h"

class GraphicsProcessorEnhancer
{
public:
	GraphicsProcessorEnhancer();

	void setSlabGraphicProperties(DgnBoxDetail dgnBoxDetail, PrimitiveCommonGraphicProperties* primitiveCommonGraphicProperties);
	void setConeGraphicProperties(DgnConeDetail dgnConeDetail, PrimitiveCommonGraphicProperties* primitiveCommonGraphicProperties);
	void setSphereGraphicProperties(PrimitiveCommonGraphicProperties* primitiveCommonGraphicProperties);
	void setTorusGraphicProperties(DgnTorusPipeDetail dgnTorusPipeDetail, double sweepRadians, DPoint3d centerOfRotation, PrimitiveCommonGraphicProperties* primitiveCommonGraphicProperties);

	ICurveGraphicProperties* processCurvePrimitives(ICurvePrimitivePtr curve);
	PrimitiveCommonGraphicProperties* PrintPrincipalAreaMoments(ISolidPrimitiveCR& primitive);
	void PrintPrincipalProperties(DRange3d& range, DVec3d& rotation, DPoint4d& qRotation, Transform& localToWorld);

	void setDictionaryProperties(DictionaryProperties& newDictionaryProperties);
	DictionaryProperties* getDictionaryProperties();
		
private:
	std::string filePath;
	DictionaryProperties* pDictionaryProperties;

};
