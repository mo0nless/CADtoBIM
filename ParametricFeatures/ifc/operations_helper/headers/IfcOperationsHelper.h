#pragma once

/**
 * @file IfcOperationsHelper.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../../../stdafx.h"
#include "../../../common/utils/headers/NumberUtils.h"
#include "../../../common/enums/headers/IfcDimensionEnum.h"
#include "../../../common/utils/headers/Comparator.h"
#include "../../../modeler/shapes/headers/ShapesGraphicProperties.h"

using namespace Common::Utilities;
using namespace Common::Enums;
using namespace Modeler::Shapes;

namespace Ifc
{
	namespace Helper
	{
		/**
		 * @brief Class that operates as a helper for the IFC geometry topology:
		 * IfcCartesianPoint, IfcDirection, IfcAxis2Placement3D, ...
		 * 
		 */
		class IfcOperationsHelper
		{
		public:
			IfcOperationsHelper();

			/**
			 * @brief Build an IfcCartesianPoint 3D from Bentley DPoint3d
			 * 
			 * @remark 3D Dimension
			 * @param newControlPoint 
			 * @return Ifc4::IfcCartesianPoint* 
			 */
			static Ifc4::IfcCartesianPoint* buildIfcCartesian3DfromCoordsPoint3D(DPoint3d newControlPoint);

			/**
			 * @brief Build an IfcCartesianPoint 2D from Bentley DPoint3d
			 * 
			 * @remark 2D Dimension
			 * @param newControlPoint 
			 * @return Ifc4::IfcCartesianPoint* 
			 */
			static Ifc4::IfcCartesianPoint* buildIfcCartesian2DfromCoordsPoint3D(DPoint3d newControlPoint);

			/**
			 * @brief Build an IfcDirection 3D from Bentley DVec3d
			 * 
			 * @remark 3D Dimension
			 * @param newDirection 
			 * @return Ifc4::IfcDirection* 
			 */
			static Ifc4::IfcDirection* buildIfcDirection3DfromDirectionVec3D(DVec3d newDirection);

			/**
			 * @brief Build an IfcDirection 2D from Bentley DVec3d
			 * 
			 * @remark 2D Dimension
			 * @param newDirection 
			 * @return Ifc4::IfcDirection* 
			 */
			static Ifc4::IfcDirection* buildIfcDirection2DfromDirectionVec3D(DVec3d newDirection);

			/**
			 * @brief Build an IfcAxis2Placement3D 3D from Bentley DVec3d
			 * 
			 * @param pointOfPlacement 
			 * @param dirVectorZ 
			 * @param dirVectorX 
			 * @return Ifc4::IfcAxis2Placement3D* 
			 */
			static Ifc4::IfcAxis2Placement3D * buildIfcAxis2Placement3D(DVec3d pointOfPlacement, DVec3d dirVectorZ, DVec3d dirVectorX);
			
			/**
			 * @brief Build an IfcAxis2Placement2D 2D from Bentley DVec3d
			 * 
			 * @param pointOfPlacement 
			 * @param dirVectorX 
			 * @return Ifc4::IfcAxis2Placement2D* 
			 */
			static Ifc4::IfcAxis2Placement2D * buildIfcAxis2Placement2D(DVec3d pointOfPlacement, DVec3d dirVectorX);

			/**
			 * @brief Check if two are equal triplet (DVec3d or DPoint3d)
			 * 
			 * @tparam Triplet3D e.g. DVec3d DPoint3d
			 * @param firstTriplet 
			 * @param secondTriplet 
			 * @return true 
			 * @return false 
			 */
			template<class Triplet3D>
			static bool areTripletsDoubleEqual(Triplet3D firstTriplet, Triplet3D secondTriplet);
			
			/**
			 * @brief Build an IfcVector from Bentley DVec3d or DPoint3d
			 * 
			 * @tparam Triplet3D 
			 * @param newVector 
			 * @return Ifc4::IfcVector* 
			 */
			template<class Triplet3D>
			static Ifc4::IfcVector* buildIfcVectorFromDirectionPoint3D(Triplet3D newVector);

			/**
			 * @brief Adjust the XY Plane of the ShapeGraphicProperties
			 * 
			 * @param shape 
			 * @param position 
			 * @param rotatePoint 
			 */
			static void adjustShapeGlobalPlacement(ShapesGraphicProperties* shape, DVec3d position, bool rotatePoint);

			/**
			 * @brief Rotate DPoint3d along a specific axis
			 * 
			 * @param axis 
			 * @param oldPoint 
			 * @return DPoint3d 
			 */
			static DPoint3d rotateAlongAxis(string axis, DPoint3d oldPoint);

		private:	
			/**
			 * @brief Build a vector<double> 3D from Bentley DVec3d or DPoint3d
			 * 
			 * @tparam Triplet3D DVec3d or DPoint3d
			 * @param newTriplet 
			 * @return vector<double> 
			 */
			template<class Triplet3D>
			static vector<double> buildDoubleVectorFromTriplet(Triplet3D newTriplet);

			/**
			 * @brief Build a vector<double> 2D from Bentley DVec3d or DPoint3d
			 * 
			 * @tparam Tuple2D DVec3d or DPoint3d
			 * @param newTuple 
			 * @return vector<double> 
			 */
			template<class Tuple2D>
			static vector<double> buildDoubleVectorFromTuple(Tuple2D newTuple);
		};

		//Dpoint3d, Dvec3d
		template<class Triplet3D>
		Ifc4::IfcVector * IfcOperationsHelper::buildIfcVectorFromDirectionPoint3D(Triplet3D newVector)
		{
			Ifc4::IfcDirection* dir = new Ifc4::IfcDirection(
				IfcOperationsHelper::buildDoubleVectorFromTriplet<Triplet3D>(newVector)
			);

			Ifc4::IfcVector* vC = new Ifc4::IfcVector(dir, newVector.Magnitude());

			return vC;
		}

		//Dpoint3d, Dvec3d
		template<class Triplet3D>
		inline bool IfcOperationsHelper::areTripletsDoubleEqual(Triplet3D firstTriplet, Triplet3D secondTriplet)
		{
			for (int i = 0; i < 3; i++)
			{
				if (Comparator::isEqual(firstTriplet.GetComponent(i), secondTriplet.GetComponent(i)))
				{
					continue;
				}
				else return false;
			}

			return true;
		}

		template<class Triplet3D>
		inline vector<double> IfcOperationsHelper::buildDoubleVectorFromTriplet(Triplet3D newTriplet)
		{
			vector<double> points;
			points.push_back(NumberUtils::convertCurrentUnitToMeters(newTriplet.x));
			points.push_back(NumberUtils::convertCurrentUnitToMeters(newTriplet.y));
			points.push_back(NumberUtils::convertCurrentUnitToMeters(newTriplet.z));

			return points;
		}

		template<class Tuple2D>
		inline vector<double> IfcOperationsHelper::buildDoubleVectorFromTuple(Tuple2D newTuple)
		{
			vector<double> points;
			points.push_back(NumberUtils::convertCurrentUnitToMeters(newTuple.x));
			points.push_back(NumberUtils::convertCurrentUnitToMeters(newTuple.y));

			return points;
		}
	}
}



