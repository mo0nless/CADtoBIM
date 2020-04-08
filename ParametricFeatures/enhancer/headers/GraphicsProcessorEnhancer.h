#pragma once

#include "../../headers/PropertiesReaderProcessor.h"
//#include "../../modeler/properties/primitives/graphic/headers/PrimitiveGraphicProperties.h"
#include "../../modeler/properties/curves/headers/CurvesShapesPrimitives.h"
#include "../../modeler/properties/primitives/graphic/headers/ConeGraphicProperties.h"
#include "../../modeler/properties/primitives/graphic/headers/CylinderGraphicProperties.h"
#include "../../modeler/properties/primitives/graphic/headers/BoxGraphicProperties.h"
#include "../../modeler/properties/primitives/graphic/headers/SphereGraphicProperties.h"
#include "../../modeler/properties/primitives/graphic/headers/TorusGraphicProperties.h"

class GraphicsProcessorEnhancer
{
public:
	GraphicsProcessorEnhancer();

	void setBoxGraphicProperties(DgnBoxDetail dgnBoxDetail, BoxGraphicProperties*& BoxGraphicProperties);
	void setConeGraphicProperties(DgnConeDetail dgnConeDetail, ConeGraphicProperties*& coneGraphicProperties);
	void setCylinderGraphicProperties(DgnConeDetail dgnConeDetail, CylinderGraphicProperties*& cylinderGraphicProperties);
	void setSphereGraphicProperties(SphereGraphicProperties*& sphereGraphicProperties);
	void setTorusGraphicProperties(DgnTorusPipeDetail dgnTorusPipeDetail, double sweepRadians, DPoint3d centerOfRotation, TorusGraphicProperties*& torusGraphicProperties);
	SolidPrimitiveProperty* handleConeAndCylinder(DgnConeDetail dgnConeDetail);
	void processConeAndCylinder(ISolidPrimitiveCR& primitive);



	ICurveGraphicProperties* processCurvePrimitives(ICurvePrimitivePtr curve);

	// use this method to set centroid, area and volume
	void PrintPrincipalAreaMoments(ISolidPrimitiveCR& primitive, GraphicProperties*& GraphicProperties);

	// use this method to set vector axis X,Y,Z
	void setGraphicPropertiesAxes(GraphicProperties*& GraphicProperties, Transform& localToWorld, const double parametrizationSign = 1);
	void PrintPrincipalProperties(DRange3d& range, DVec3d& rotation, DPoint4d& qRotation, Transform& localToWorld);

	void setDictionaryProperties(DictionaryProperties& newDictionaryProperties);
	DictionaryProperties* getDictionaryProperties();
		
private:
	std::string filePath;
	DictionaryProperties* pDictionaryProperties;

};
