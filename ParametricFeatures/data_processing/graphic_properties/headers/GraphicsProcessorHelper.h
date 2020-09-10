#pragma once


#include "../../../logging/headers/Logger.h"

#include "../../reader_properties/headers/PropertiesReaderProcessor.h"
#include "../../../modeler/brep_solids/headers/BRepGraphicProperties.h"
#include "../../../modeler/shapes/headers/CurvesShapesGraphicProperties.h"

#include "../../../modeler/primitives/headers/ConeGraphicProperties.h"
#include "../../../modeler/primitives/headers/CylinderGraphicProperties.h"
#include "../../../modeler/primitives/headers/BoxGraphicProperties.h"
#include "../../../modeler/primitives/headers/SphereGraphicProperties.h"
#include "../../../modeler/primitives/headers/TorusGraphicProperties.h"
#include "../../../modeler/primitives/headers/RotationalSweepGraphicProperties.h"
#include "../../../modeler/primitives/headers/RuledSweepGraphicProperties.h"
#include "../../../modeler/primitives/headers/ExtrusionGraphicProperties.h"
#include "../../../modeler/brep_solids/headers/SolidEntityGraphicProperties.h"

#include "PolyfaceConvertTool.h"
#include <math.h>

#include "../../../modeler/data_writer/headers/ModelerDataWriterManager.h"

#include "../../../common/utils/headers/Comparator.h"

class GraphicsProcessorHelper
{

private:
	ElementBundle* elementBundle;
	string filePath;
	DictionaryProperties* pDictionaryProperties;

	ModelerDataWriterManager* _modelerDataWriterManager;

	template <class T, class U>
	T searchOnMap(map<U, T>, U key);

	ElementHandle _currentElementHandle;

public:
	GraphicsProcessorHelper();

	void setBoxGraphicProperties(DgnBoxDetail dgnBoxDetail, BoxGraphicProperties*& BoxGraphicProperties);
	void setConeGraphicProperties(DgnConeDetail dgnConeDetail, ConeGraphicProperties*& coneGraphicProperties);
	void setCylinderGraphicProperties(DgnConeDetail dgnConeDetail, CylinderGraphicProperties*& cylinderGraphicProperties);
	void setSphereGraphicProperties(SphereGraphicProperties*& sphereGraphicProperties);
	void setTorusGraphicProperties(DgnTorusPipeDetail dgnTorusPipeDetail, double sweepRadians, DPoint3d centerOfRotation, TorusGraphicProperties*& torusGraphicProperties);
	void setRotationalSweepGraphicProperties(DgnRotationalSweepDetail dgnRotationalSweepDetail, RotationalSweepGraphicProperties*& rotationalSweepGraphicProperties);
	void setRuledSweepGraphicProperties(DgnRuledSweepDetail ruledSweepDetails, RuledSweepGraphicProperties*& ruledSweepGraphicProperties);
	void setExtrusionGraphicProperties(DgnExtrusionDetail extrusionDetails, ExtrusionGraphicProperties*& extrusionGraphicProperties);
	
	GraphicProperties* processConeAndCylinder(ISolidPrimitiveCR& primitive);
	void processMSBsplineSurface(MSBsplineSurfaceCR msBsplineSurface, MSBsplineSurfaceGraphicProperties* msBsplineSurfaceGraphicProperties = nullptr, bool addToDictionary = true);
	void processShapesCurvesVector(CurveVectorCR& curvesVector, bool isFilled, ShapesGraphicProperties* shapesGraphicProperties = nullptr, bool addToDictionary = true);
	void processCurvesPrimitives(CurveVectorCR& curvesVector, ShapesGraphicProperties*& shapesGraphicProperties);
	GraphicProperties* processSolidPrimitives(ISolidPrimitiveCR& primitive, bool addToDictionary = true);
	void processBodySolid(ISolidKernelEntityCR entity, bool meshProcessing = false);
	
	void evaluateUVShapesCurvesVector(MSBsplineSurfaceCR msBsplineSurface, ShapesGraphicProperties*& shapesGraphicProperties, MSBsplineSurfaceGraphicProperties*& msBsplineSurfaceGraphicProperties);
	
	void setGraphicPropertiesAxes(GraphicProperties*& GraphicProperties, Transform& localToWorld);// use this method to set vector axis X,Y,Z
	void setSolidPrimCentroidAreaVolume(ISolidPrimitiveCR& primitive, GraphicProperties*& GraphicProperties);// use this method to set centroid, area and volume

	void setDictionaryProperties(DictionaryProperties& newDictionaryProperties);
	void setElementBundle(ElementBundle& newElementBundle);
	ElementBundle* getElementBundle();

	DictionaryProperties* getDictionaryProperties();
	
	bool processPolyfaceFacets(PolyfaceQueryCR meshData, bool isFilled, Transform currentTransform);
	bool processElementAsMesh(SolidEntityGraphicProperties*& bRepGraphicProperties, bvector<PolyfaceHeaderPtr> meshes);
	bool ElementToApproximateFacets(ElementHandleCR source, bvector<PolyfaceHeaderPtr> &output, IFacetOptionsP options);


	ElementHandle getCurrentElementHandle();
	void setElementHandle(ElementHandle elementHandle);	
};

template <class T, class U>
inline T GraphicsProcessorHelper::searchOnMap(map<U, T> mappedValues, U key)
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
