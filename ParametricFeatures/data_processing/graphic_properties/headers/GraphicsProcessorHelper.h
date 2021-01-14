#pragma once

/**
 * @file GraphicsProcessorHelper.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-14
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <math.h>

#include "../../../logging/headers/Logger.h"

#include "../../reader_properties/headers/PropertiesReaderProcessor.h"
#include "../../../ifc/bundle/headers/IfcElementBundle.h"

#include "../../../modeler/shapes/headers/ShapesGraphicProperties.h"
#include "../../../modeler/curves/headers/CurveGraphicProperties.h"
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
#include "../../../modeler/surfaces/headers/MSBsplineSurfaceGraphicProperties.h"


#include "PolyfaceConvertTool.h"

#include "../../../modeler/data_writer/headers/ModelerDataWriterManager.h"

#include "../../../common/utils/headers/Comparator.h"

/** @ingroup data_processing Data Processing
*  @{
*/

using namespace Ifc::Bundle;
using namespace Common::Utilities;
using namespace Modeler;
using namespace Modeler::BRepSolids;
using namespace Modeler::Curves;
using namespace Modeler::Shapes;
using namespace Modeler::Surfaces;
using namespace Modeler::TextString;
using namespace Modeler::DataWriter;

namespace DataProcessing
{
	namespace GraphicsProperties
	{
		/**
		 * @brief Class helper for extract geometry information through the Graphic Processor
		 * 
		 * @see GraphicProcessor
		 */
		class GraphicsProcessorHelper
		{

		private:
			IfcGraphicPropertiesBundle* _ifcGraphicPropertiesBundle;
			ElementHandle _currentElementHandle;
			IfcElementBundle* _ifcElementBundle;

			ModelerDataWriterManager* _modelerDataWriterManager;

			Logging::Logger* _logger = Logging::Logger::getLogger();

			template <class T, class U>
			T searchOnMap(map<U, T>, U key);
		public:
			GraphicsProcessorHelper();

#pragma region PRIMITIVES SETTER
			/**
			 * @brief Set the Box Graphic Properties object
			 * 
			 * @param dgnBoxDetail 
			 * @param BoxGraphicProperties 
			 */
			void setBoxGraphicProperties(DgnBoxDetail dgnBoxDetail, BoxGraphicProperties*& BoxGraphicProperties);
			
			/**
			 * @brief Set the Cone Graphic Properties object
			 * 
			 * @param dgnConeDetail 
			 * @param coneGraphicProperties 
			 */
			void setConeGraphicProperties(DgnConeDetail dgnConeDetail, ConeGraphicProperties*& coneGraphicProperties);
			
			/**
			 * @brief Set the Cylinder Graphic Properties object
			 * 
			 * @param dgnConeDetail 
			 * @param cylinderGraphicProperties 
			 */
			void setCylinderGraphicProperties(DgnConeDetail dgnConeDetail, CylinderGraphicProperties*& cylinderGraphicProperties);
			
			/**
			 * @brief Set the Sphere Graphic Properties object
			 * 
			 * @param sphereGraphicProperties 
			 */
			void setSphereGraphicProperties(SphereGraphicProperties*& sphereGraphicProperties);
			
			/**
			 * @brief Set the Torus Graphic Properties object
			 * 
			 * @param dgnTorusPipeDetail 
			 * @param sweepRadians 
			 * @param centerOfRotation 
			 * @param torusGraphicProperties 
			 */
			void setTorusGraphicProperties(DgnTorusPipeDetail dgnTorusPipeDetail, double sweepRadians, DPoint3d centerOfRotation, TorusGraphicProperties*& torusGraphicProperties);
			
			/**
			 * @brief Set the Rotational Sweep Graphic Properties object
			 * 
			 * @param dgnRotationalSweepDetail 
			 * @param rotationalSweepGraphicProperties 
			 */
			void setRotationalSweepGraphicProperties(DgnRotationalSweepDetail dgnRotationalSweepDetail, RotationalSweepGraphicProperties*& rotationalSweepGraphicProperties);
			
			/**
			 * @brief Set the Ruled Sweep Graphic Properties object
			 * 
			 * @param ruledSweepDetails 
			 * @param ruledSweepGraphicProperties 
			 */
			void setRuledSweepGraphicProperties(DgnRuledSweepDetail ruledSweepDetails, RuledSweepGraphicProperties*& ruledSweepGraphicProperties);

			/**
			 * @brief Set the Extrusion Graphic Properties object
			 * 
			 * @param extrusionDetails 
			 * @param extrusionGraphicProperties 
			 */
			void setExtrusionGraphicProperties(DgnExtrusionDetail extrusionDetails, ExtrusionGraphicProperties*& extrusionGraphicProperties);
#pragma endregion

#pragma region GEN. PROPERTIES
			/**
			 * @brief Set the Graphic Properties Axes object. Use this method to set vector axis X,Y,Z
			 * 
			 * @param GraphicProperties 
			 * @param localToWorld 
			 */
			void setGraphicPropertiesAxes(GraphicProperties*& GraphicProperties, Transform& localToWorld);
			
			/**
			 * @brief Set the Solid Prim Centroid Area Volume object. Use this method to set centroid, area and volume
			 * 
			 * @param primitive 
			 * @param GraphicProperties 
			 */
			void setSolidPrimCentroidAreaVolume(ISolidPrimitiveCR& primitive, GraphicProperties*& GraphicProperties);
#pragma endregion

#pragma region PROCESSORS SETUP CALL
			/**
			 * @brief Processing call of Text properties
			 * 
			 * @param text 
			 * @return true 
			 * @return false 
			 * 
			 * @see GraphicProcessor
			 */
			bool processTextString(TextStringCR text);

			/**
			 * @brief Processing call of BSpline Surface properties
			 * 
			 * @param msBsplineSurface 
			 * @return true 
			 * @return false 
			 */
			bool processMSBsplineSurface(MSBsplineSurfaceCR msBsplineSurface);

			/**
			 * @brief Processing call of Shapes Curve Vector properties
			 * 
			 * @param curvesVector 
			 * @param isFilled 
			 * @return true 
			 * @return false 
			 */
			bool processShapesCurvesVector(CurveVectorCR& curvesVector, bool isFilled);

			/**
			 * @brief Processing call of Primitives properties
			 * 
			 * @param primitive 
			 * @return true 
			 * @return false 
			 */
			bool processSolidPrimitive(ISolidPrimitiveCR& primitive);

			/**
			 * @brief Processing call of Polyface Mesh properties
			 * 
			 * @param meshData 
			 * @param isFilled 
			 * @param currentTransform 
			 * @return true 
			 * @return false 
			 */
			bool processPolyfaceFacets(PolyfaceQueryCR meshData, bool isFilled, Transform currentTransform);
#pragma endregion

#pragma region PROCESSORS EXECUTION
			/**
			 * @brief Process Cone and Cylinder
			 * 
			 * @param primitive 
			 * @return GraphicProperties* 
			 */
			GraphicProperties* processConeAndCylinder(ISolidPrimitiveCR& primitive);

			/**
			 * @brief Process Primitives
			 * 
			 * @param primitive 
			 * @return GraphicProperties* 
			 */
			GraphicProperties* processPrimitives(ISolidPrimitiveCR& primitive);

			/**
			 * @brief Process Text
			 * 
			 * @param text 
			 * @param textGraphicProperties 
			 * @return true 
			 * @return false 
			 */
			bool processTextString(TextStringCR text, TextGraphicProperties* textGraphicProperties);

			/**
			 * @brief Process BSpline Surface
			 * 
			 * @param msBsplineSurface 
			 * @param msBsplineSurfaceGraphicProperties 
			 */
			void processMSBsplineSurface(MSBsplineSurfaceCR msBsplineSurface, MSBsplineSurfaceGraphicProperties* msBsplineSurfaceGraphicProperties);
			
			/**
			 * @brief BSpline UV coords evaluation
			 * 
			 * @param msBsplineSurface 
			 * @param shapesGraphicProperties 
			 * @param msBsplineSurfaceGraphicProperties 
			 */
			void evaluateUVShapesCurvesVector(MSBsplineSurfaceCR msBsplineSurface, ShapesGraphicProperties*& shapesGraphicProperties, MSBsplineSurfaceGraphicProperties*& msBsplineSurfaceGraphicProperties);

			/**
			 * @brief Process Curve Vector Shape
			 * 
			 * @param curvesVector 
			 * @param isFilled 
			 * @param shapesGraphicProperties 
			 */
			void processShapesCurvesVector(CurveVectorCR& curvesVector, bool isFilled, ShapesGraphicProperties* shapesGraphicProperties);
			
			/**
			 * @brief Process Curve Primitives
			 * 
			 * @param curvesVector 
			 * @param shapesGraphicProperties 
			 */
			void processCurvesPrimitives(CurveVectorCR& curvesVector, ShapesGraphicProperties*& shapesGraphicProperties);

			/**
			 * @brief Process Body solid
			 * 
			 * @param entity 
			 * @param meshProcessing 
			 */
			void processBodySolid(ISolidKernelEntityCR entity, bool meshProcessing = false);

			/**
			 * @brief Process as Mesh
			 * 
			 * @param bRepGraphicProperties 
			 * @param meshes 
			 * @return true 
			 * @return false 
			 */
			bool processElementAsMesh(SolidEntityGraphicProperties*& bRepGraphicProperties, bvector<PolyfaceHeaderPtr> meshes);

			/**
			 * @brief Process triangulated faces Approximation
			 * 
			 * @param source 
			 * @param output 
			 * @param options 
			 * @return true 
			 * @return false 
			 */
			bool ElementToApproximateFacets(ElementHandleCR source, bvector<PolyfaceHeaderPtr> &output, IFacetOptionsP options);
#pragma endregion
			/**
			 * @brief Set the Ifc Element Bundle object
			 * 
			 * @param newIfcElementBundle 
			 */
			void setIfcElementBundle(IfcElementBundle& newIfcElementBundle);

			/**
			 * @brief Set the Ifc Graphic Properties Bundle object
			 * 
			 * @param newIfcGraphicPropertiesBundle 
			 */
			void setIfcGraphicPropertiesBundle(IfcGraphicPropertiesBundle& newIfcGraphicPropertiesBundle);

			/**
			 * @brief Set the Element Handle object
			 * 
			 * @param elementHandle 
			 */
			void setElementHandle(ElementHandle elementHandle);

			IfcGraphicPropertiesBundle* getIfcGraphicPropertiesBundle();
			IfcElementBundle* getIfcElementBundle();
			ElementHandle getCurrentElementHandle();
		};

		/**
		 * @brief Search up Template map
		 * 
		 * @tparam T 
		 * @tparam U 
		 * @param mappedValues 
		 * @param key 
		 * @return T 
		 */
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
	}
}
/** @} */ // end of Data Processing