#pragma once

#include "../../headers/PropertiesReaderProcessor.h"
//#include "../../modeler/properties/primitives/graphic/headers/PrimitiveGraphicProperties.h"
#include "../../modeler/properties/curves/headers/CurvesPrimitivesContainer.h"
#include "../../modeler/properties/primitives/graphic/headers/ConeGraphicProperties.h"
#include "../../modeler/properties/primitives/graphic/headers/CylinderGraphicProperties.h"

class GraphicsProcessorEnhancer
{
public:
	GraphicsProcessorEnhancer();

	//void setSlabGraphicProperties(DgnBoxDetail dgnBoxDetail, PrimitiveCommonGraphicProperties* primitiveCommonGraphicProperties);
	void setConeGraphicProperties(DgnConeDetail dgnConeDetail, ConeGraphicProperties*& coneGraphicProperties);
	void setCylinderGraphicProperties(DgnConeDetail dgnConeDetail, CylinderGraphicProperties*& cylinderGraphicProperties);
	SolidPrimitiveProperty* handleConeAndCylinder(DgnConeDetail dgnConeDetail);

	//void setSphereGraphicProperties(PrimitiveCommonGraphicProperties* primitiveCommonGraphicProperties);
	//void setTorusGraphicProperties(DgnTorusPipeDetail dgnTorusPipeDetail, double sweepRadians, DPoint3d centerOfRotation, PrimitiveCommonGraphicProperties* primitiveCommonGraphicProperties);

	ICurveGraphicProperties* processCurvePrimitives(ICurvePrimitivePtr curve);

	// use this method to set centroid, area and volume
	void PrintPrincipalAreaMoments(ISolidPrimitiveCR& primitive, GraphicProperty*& graphicProperty);

	// use this method to set vector axis X,Y,Z
	void setGraphicPropertyAxes(GraphicProperty*& graphicProperty, Transform& localToWorld, const double parametrizationSign = 1);
	void PrintPrincipalProperties(DRange3d& range, DVec3d& rotation, DPoint4d& qRotation, Transform& localToWorld);

	void setDictionaryProperties(DictionaryProperties& newDictionaryProperties);
	DictionaryProperties* getDictionaryProperties();
		
private:
	std::string filePath;
	DictionaryProperties* pDictionaryProperties;

};
