#pragma once

#include "../../headers/PropertiesReaderProcessor.h"
//#include "../../modeler/properties/brep_solids/headers/SolidEntityGraphicProperties.h"
#include "../../modeler/properties/brep_solids/headers/BRepGraphicProperties.h"
#include "../../modeler/properties/shapes/headers/CurvesShapesGraphicProperties.h"

#include "../../modeler/properties/primitives/graphic/headers/ConeGraphicProperties.h"
#include "../../modeler/properties/primitives/graphic/headers/CylinderGraphicProperties.h"
#include "../../modeler/properties/primitives/graphic/headers/BoxGraphicProperties.h"
#include "../../modeler/properties/primitives/graphic/headers/SphereGraphicProperties.h"
#include "../../modeler/properties/primitives/graphic/headers/TorusGraphicProperties.h"
#include "../../modeler/properties/brep_solids/headers/SolidEntityGraphicProperties.h"

#include "PolyfaceConvertTool.h"
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
	
	void processConeAndCylinder(ISolidPrimitiveCR& primitive);
	void processMSBsplineSurface(MSBsplineSurfaceCR msBsplineSurface, MSBsplineSurfaceGraphicProperties*& msBsplineSurfaceGraphicProperties);
	void processShapesCurvesVector(CurveVectorCR& curvesVector, bool isFilled, ShapesGraphicProperties* shapesGraphicProperties = nullptr, bool addToDictionary = true);
	void processCurvesPrimitives(CurveVectorCR& curvesVector, ShapesGraphicProperties*& shapesGraphicProperties);
	
	
	void setGraphicPropertiesAxes(GraphicProperties*& GraphicProperties, Transform& localToWorld);// use this method to set vector axis X,Y,Z
	void PrintPrincipalProperties(DRange3d& range, DVec3d& rotation, DPoint4d& qRotation, Transform& localToWorld);	
	void PrintPrincipalAreaMoments(ISolidPrimitiveCR& primitive, GraphicProperties*& GraphicProperties);// use this method to set centroid, area and volume

	bool isDoubleEqual(double x, double y);	

	void setDictionaryProperties(DictionaryProperties& newDictionaryProperties);
	DictionaryProperties* getDictionaryProperties();
	
	bool processEntityAsFacetedBRep(ISolidKernelEntityCR entity);
	bool processElementAsMesh();
	bool ElementToApproximateFacets(ElementHandleCR source, bvector<PolyfaceHeaderPtr> &output, IFacetOptionsP options);

	ElementHandle mCurrentElementHandle;
	BRepGraphicProperties* mBRepGraphicProperties = nullptr;
private:
	std::string filePath;
	DictionaryProperties* pDictionaryProperties;
	
	template<class T>
	T searchOnMap(std::map<int, T>, int key);
};

template<class T>
inline T GraphicsProcessorEnhancer::searchOnMap(std::map<int, T> mappedValues, int key)
{
	for (auto const& element : mappedValues)
	{
		if (element.first == key)
		{
			return element.second;
		}
	}
	return NULL;
}
