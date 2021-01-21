#pragma once

/**
 * @file IfcShapesEnhancer.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../../../../stdafx.h"

#include "../../../../modeler/curves/headers/CurveGraphicProperties.h"
#include "../../../../modeler/shapes/headers/ShapesGraphicProperties.h"
#include "../../../../common/utils/headers/ShapesTypeEnumUtils.h"
#include "../../../../common/enums/headers/ShapesTypeEnum.h"
#include "../../../bundle/headers/IfcElementBundle.h"
#include <vector>

using namespace Ifc::Bundle;
using namespace Common;
using namespace Common::Enums;
using namespace Common::Utilities;
using namespace Modeler::Curves;
using namespace Modeler::Shapes;

namespace Ifc
{
	namespace GeometricRepresentation
	{
		/**
		 * @brief Container structure that store the result of the IfcShapeEnhancer
		 * 
		 * @remark needs for data exchange when processing shape curves from other enhancer: IfcPrimitivesEnhancer IfcBRepSolidsEnhancer
		 */
		struct BoundTypeIfcCurve
		{
			CurvesBoundaryTypeEnum boundary;
			Ifc4::IfcCurve* ifcCurve;
			vector<Ifc4::IfcCurve*> vecIfcCurves;
			vector<CurveGraphicProperties*> vecPrimitivesCurves;
			bool isClosed = false;
			DPoint3d start, end;
		};

		/**
		 * @brief Ifc Primitives Class Enhancer. Process the SolidEntityGraphicProperties to build CSG Primitives solid IFC representation
		 * 
		 * @remark the function is called mainly by the class IfcBuilder as external use from IfcBRepSolidsEnhancer, IfcPrimitivesEnhancer
		 * @see IfcBuilder IfcBRepSolidsEnhancer IfcPrimitivesEnhancer
		 */
		class IfcShapesEnhancer
		{
		public:
			IfcShapesEnhancer();

			/**
			 * @brief Enhancer that handle the processing process
			 * 
			 * @param file the Ifc file helper
			 * @param shapeGraphicProperties the Shape Curve Vector graphic properties
			 * @param ifcElementBundle the Element in which the Shape Curve Vector belongs
			 * @param ifcGraphicPropertiesBundle  the ifcGraphicPropertiesBundle 
			 */
			void enhance(IfcHierarchyHelper<Ifc4>& file, ShapesGraphicProperties* shapeGraphicProperties, IfcElementBundle*& ifcElementBundle,
				IfcGraphicPropertiesBundle* ifcGraphicPropertiesBundle, bool addToIfcElementBundle = true);

			/**
			 * @brief Check if the Shape curve vector is a single item
			 * 
			 * @return true 
			 * @return false 
			 */
			bool hasSingleShapeItem();

			/**
			 * @brief Get the Single Shape Representation object
			 * 
			 * @return Ifc4::IfcGeometricRepresentationItem* 
			 */
			Ifc4::IfcGeometricRepresentationItem* getSingleShapeRepresentation();

			/**
			 * @brief Get the Curves Shape Representation (BoundTypeIfcCurve) Vector object
			 * 
			 * @return vector<BoundTypeIfcCurve*> 
			 */
			vector<BoundTypeIfcCurve*> getCurvesShapeRepresentationVector();

			/**
			 * @brief Dimension 2D or 3D of the curve 
			 * 
			 */
			IfcDimensionEnum dimension = IfcDimensionEnum::dim_3D;
			bool uvCoordsParse = false;

		private:
			Logging::Logger* _logger = Logging::Logger::getLogger();

			/**
			 * @brief The builder of the IfcCurve (IfcGeometricRepresentationItem) of a single curve
			 * 
			 * @param curveProperties 
			 * @param file 
			 * @param ifcElementBundle 
			 * @return Ifc4::IfcCurve* 
			 */
			Ifc4::IfcCurve* buildIfcCurvePrimitives(CurveGraphicProperties* curveProperties, IfcHierarchyHelper<Ifc4>& file, IfcElementBundle*& ifcElementBundle);
			
			/**
			 * @brief build an IfcCompositeCurveSegment from all the parsed single curves (IfcCurve) vector
			 * 
			 * @param curveVector 
			 * @return IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>* 
			 */
			IfcTemplatedEntityList<Ifc4::IfcCompositeCurveSegment>* buildIfcCompositeCurveSegment(vector<Ifc4::IfcCurve*> curveVector);

			/**
			 * @brief Parse all the Shape curves Graphic Properties and generate the single curves (IfcCurve) vector
			 * 
			 * @param curvesShape 
			 * @param file 
			 * @param ifcElementBundle 
			 * @return vector<Ifc4::IfcCurve*> 
			 */
			vector<Ifc4::IfcCurve*> ifcShapesCurvesParser(ShapesGraphicProperties* curvesShape, IfcHierarchyHelper<Ifc4>& file, IfcElementBundle*& ifcElementBundle);

			Ifc4::IfcGeometricRepresentationItem* mSingleShapeRepresentation;

			/**
			 * @brief the vector of the BoundTypeIfcCurve container 
			 * 
			 */
			vector<BoundTypeIfcCurve*> mShapeBoundTypeCurvesVector;
			bool mHasSingleShape;
		};

	}
}