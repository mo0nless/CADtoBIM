#pragma once

#include "../../headers/PropertiesReaderProcessor.h"
//#include "../../modeler/properties/primitives/graphic/headers/PrimitiveGraphicProperties.h"
#include "../../modeler/properties/shapes/headers/CurvesShapesGraphicProperties.h"
#include "../../modeler/properties/shapes/headers/CircleShapesGraphicProperties.h"
#include "../../modeler/properties/shapes/headers/ComplexChainShapesGraphicProperties.h"
#include "../../modeler/properties/shapes/headers/EllipseShapesGraphicProperties.h"
#include "../../modeler/properties/shapes/headers/GenericShapesGraphicProperties.h"

#include "../../modeler/properties/primitives/graphic/headers/ConeGraphicProperties.h"
#include "../../modeler/properties/primitives/graphic/headers/CylinderGraphicProperties.h"
#include "../../modeler/properties/primitives/graphic/headers/BoxGraphicProperties.h"
#include "../../modeler/properties/primitives/graphic/headers/SphereGraphicProperties.h"
#include "../../modeler/properties/primitives/graphic/headers/TorusGraphicProperties.h"
#include "../../modeler/properties/primitives/graphic/headers/RotationalSweepGraphicProperties.h"

#include <math.h>

class GraphicsProcessorEnhancer
{
public:
	GraphicsProcessorEnhancer();

	void setBoxGraphicProperties(DgnBoxDetail dgnBoxDetail, BoxGraphicProperties*& BoxGraphicProperties);
	void setConeGraphicProperties(DgnConeDetail dgnConeDetail, ConeGraphicProperties*& coneGraphicProperties);
	void setCylinderGraphicProperties(DgnConeDetail dgnConeDetail, CylinderGraphicProperties*& cylinderGraphicProperties);
	void setSphereGraphicProperties(SphereGraphicProperties*& sphereGraphicProperties);
	void setTorusGraphicProperties(DgnTorusPipeDetail dgnTorusPipeDetail, double sweepRadians, DPoint3d centerOfRotation, TorusGraphicProperties*& torusGraphicProperties);
	void setRotationalSweepGraphicProperties(DgnRotationalSweepDetail dgnRotationalSweepDetail, DPoint3d centerOfRotation, RotationalSweepGraphicProperties*& rotationalSweepGraphicProperties);
	void processConeAndCylinder(ISolidPrimitiveCR& primitive);

	void processShapesCurvesVector(CurveVectorCR& curves, bool isFilled , ShapesGraphicProperties*& shapesGraphicProperties);
	CurveGraphicProperties* processCurvePrimitives(ICurvePrimitivePtr curve);

	// use this method to set centroid, area and volume
	void PrintPrincipalAreaMoments(ISolidPrimitiveCR& primitive, GraphicProperties*& GraphicProperties);

	// use this method to set vector axis X,Y,Z
	void setGraphicPropertiesAxes(GraphicProperties*& GraphicProperties, Transform& localToWorld);
	void PrintPrincipalProperties(DRange3d& range, DVec3d& rotation, DPoint4d& qRotation, Transform& localToWorld);

	bool isDoubleEqual(double x, double y);	

	void setDictionaryProperties(DictionaryProperties& newDictionaryProperties);
	DictionaryProperties* getDictionaryProperties();
		
private:
	std::string filePath;
	DictionaryProperties* pDictionaryProperties;

};
