#pragma once

#include <math.h>

#include "../../../logging/headers/Logger.h"

#include "../../reader_properties/headers/PropertiesReaderProcessor.h"
#include "../../../ifc/main/headers/IfcElementBundle.h"

#include "../../../modeler/text/headers/TextGraphicProperties.h"

#include "../../../modeler/primitives/headers/ConeGraphicProperties.h"
#include "../../../modeler/primitives/headers/CylinderGraphicProperties.h"
#include "../../../modeler/primitives/headers/BoxGraphicProperties.h"
#include "../../../modeler/primitives/headers/SphereGraphicProperties.h"
#include "../../../modeler/primitives/headers/TorusGraphicProperties.h"
#include "../../../modeler/primitives/headers/RotationalSweepGraphicProperties.h"
#include "../../../modeler/primitives/headers/RuledSweepGraphicProperties.h"
#include "../../../modeler/primitives/headers/ExtrusionGraphicProperties.h"
#include "../../../modeler/brep_solids/headers/SolidEntityGraphicProperties.h"

#include "../../../modeler/shapes/headers/ShapesGraphicProperties.h"

#include "PolyfaceConvertTool.h"

#include "../../../modeler/data_writer/headers/ModelerDataWriterManager.h"

#include "../../../common/utils/headers/Comparator.h"

class GraphicsProcessorHelper
{

private:
	IfcGraphicPropertiesBundle* _ifcGraphicPropertiesBundle;
	ElementHandle _currentElementHandle;
	IfcElementBundle* _ifcElementBundle;

	ModelerDataWriterManager* _modelerDataWriterManager;

	Logs::Logger* _logger = Logs::Logger::getLogger();

	template <class T, class U>
	T searchOnMap(map<U, T>, U key);
public:
	GraphicsProcessorHelper();

#pragma region PRIMITIVES SETTER
	void setBoxGraphicProperties(DgnBoxDetail dgnBoxDetail, BoxGraphicProperties*& BoxGraphicProperties);
	void setConeGraphicProperties(DgnConeDetail dgnConeDetail, ConeGraphicProperties*& coneGraphicProperties);
	void setCylinderGraphicProperties(DgnConeDetail dgnConeDetail, CylinderGraphicProperties*& cylinderGraphicProperties);
	void setSphereGraphicProperties(SphereGraphicProperties*& sphereGraphicProperties);
	void setTorusGraphicProperties(DgnTorusPipeDetail dgnTorusPipeDetail, double sweepRadians, DPoint3d centerOfRotation, TorusGraphicProperties*& torusGraphicProperties);
	void setRotationalSweepGraphicProperties(DgnRotationalSweepDetail dgnRotationalSweepDetail, RotationalSweepGraphicProperties*& rotationalSweepGraphicProperties);
	void setRuledSweepGraphicProperties(DgnRuledSweepDetail ruledSweepDetails, RuledSweepGraphicProperties*& ruledSweepGraphicProperties);
	void setExtrusionGraphicProperties(DgnExtrusionDetail extrusionDetails, ExtrusionGraphicProperties*& extrusionGraphicProperties);
#pragma endregion

#pragma region GEN. PROPERTIES
	void setGraphicPropertiesAxes(GraphicProperties*& GraphicProperties, Transform& localToWorld);// use this method to set vector axis X,Y,Z
	void setSolidPrimCentroidAreaVolume(ISolidPrimitiveCR& primitive, GraphicProperties*& GraphicProperties);// use this method to set centroid, area and volume
#pragma endregion

#pragma region PROCESSORS SETUP CALL
	bool processTextString(TextStringCR text);
	bool processMSBsplineSurface(MSBsplineSurfaceCR msBsplineSurface);
	bool processShapesCurvesVector(CurveVectorCR& curvesVector, bool isFilled);	
	bool processSolidPrimitive(ISolidPrimitiveCR& primitive);
	bool processPolyfaceFacets(PolyfaceQueryCR meshData, bool isFilled, Transform currentTransform);
#pragma endregion

#pragma region PROCESSORS EXECUTION
	GraphicProperties* processConeAndCylinder(ISolidPrimitiveCR& primitive);
	GraphicProperties* processPrimitives(ISolidPrimitiveCR& primitive);

	bool processTextString(TextStringCR text, TextGraphicProperties* textGraphicProperties);

	void processMSBsplineSurface(MSBsplineSurfaceCR msBsplineSurface, MSBsplineSurfaceGraphicProperties* msBsplineSurfaceGraphicProperties);
	void evaluateUVShapesCurvesVector(MSBsplineSurfaceCR msBsplineSurface, ShapesGraphicProperties*& shapesGraphicProperties, MSBsplineSurfaceGraphicProperties*& msBsplineSurfaceGraphicProperties);

	void processShapesCurvesVector(CurveVectorCR& curvesVector, bool isFilled, ShapesGraphicProperties* shapesGraphicProperties);
	void processCurvesPrimitives(CurveVectorCR& curvesVector, ShapesGraphicProperties*& shapesGraphicProperties);

	void processBodySolid(ISolidKernelEntityCR entity, bool meshProcessing = false);
	bool processElementAsMesh(SolidEntityGraphicProperties*& bRepGraphicProperties, bvector<PolyfaceHeaderPtr> meshes);
	bool ElementToApproximateFacets(ElementHandleCR source, bvector<PolyfaceHeaderPtr> &output, IFacetOptionsP options);
#pragma endregion

	void setIfcElementBundle(IfcElementBundle& newDictionaryProperties);
	void setIfcGraphicPropertiesBundle(IfcGraphicPropertiesBundle& newElementBundle);
	void setElementHandle(ElementHandle elementHandle);

	IfcGraphicPropertiesBundle* getIfcGraphicPropertiesBundle();
	IfcElementBundle* getIfcElementBundle();
	ElementHandle getCurrentElementHandle();
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
