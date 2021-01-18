#pragma once

/**
 * @file CurveGraphicProperties.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <sstream>
#include <DgnPlatform/ElementGeometry.h>
#include <vector>
#include "../../../common/utils/headers/ShapesTypeEnumUtils.h"
#include "../../../common/enums/headers/ShapesTypeEnum.h"

using namespace std; 
using namespace Common;
using namespace Common::Enums;
using namespace Common::Utilities;

namespace Modeler
{
	namespace Curves
	{
		/**
		 * @brief Base Graphic Properties class for a Curve
		 * 
		 */
		class CurveGraphicProperties
		{

		private:
			DPoint3d _startPoint;
			DPoint3d _endPoint;

			DPoint3d _UVstartPoint;
			DPoint3d _UVendPoint;

			int mNumCPoints;
			vector<DPoint3d> _controlPoints;
			vector<DPoint3d> _UVcontrolPoints;
			CurvesPrimitivesTypeEnum _curvesTypeEnum;

		public:
			/**
			 * @brief Construct a new Curve Graphic Properties object
			 * 
			 * @param newCurveType the Enum type of the curve
			 */
			CurveGraphicProperties(CurvesPrimitivesTypeEnum newCurveType);

			/**
			 * @brief Set the Control Points object
			 * 
			 * @param newControlPoints bvector
			 */
			void setControlPoints(bvector<DPoint3d> newControlPoints);

			/**
			 * @brief Set the Control Points object
			 * 
			 * @param newControlPoints vector
			 */
			void setControlPoints(vector<DPoint3d> newControlPoints);

			/**
			 * @brief Get the Control Points object
			 * 
			 * @return vector<DPoint3d> 
			 */
			vector<DPoint3d> getControlPoints();

			/**
			 * @brief Set the UV Control Points object
			 * 
			 * @param newControlPoints 
			 */
			void setUVcontrolPoints(vector<DPoint3d> newControlPoints);

			/**
			 * @brief Get the UV Control Points object
			 * 
			 * @return vector<DPoint3d> 
			 */
			vector<DPoint3d> getUVcontrolPoints();

			/**
			 * @brief Get the Curves Type Enum object
			 * 
			 * @return CurvesPrimitivesTypeEnum 
			 */
			CurvesPrimitivesTypeEnum getCurvesTypeEnum();

			/**
			 * @brief Set the Start End Points object
			 * 
			 * @param sPoint start point
			 * @param ePoint end point
			 */
			void setStartEndPoints(DPoint3d sPoint, DPoint3d ePoint);

			/**
			 * @brief Set the UV Start End Points object
			 * 
			 * @param sPoint start point UV
			 * @param ePoint end point UV
			 */
			void setUVstartEndPoints(DPoint3d sPoint, DPoint3d ePoint);

			/**
			 * @brief Get the UV Start Point object
			 * 
			 * @return DPoint3d 
			 */
			DPoint3d getUVstartPoint();

			/**
			 * @brief Get the UV End Point object
			 * 
			 * @return DPoint3d 
			 */
			DPoint3d getUVendPoint();

			/**
			 * @brief Get the Start Point object
			 * 
			 * @return DPoint3d 
			 */
			DPoint3d getStartPoint();

			/**
			 * @brief Get the End Point object
			 * 
			 * @return DPoint3d 
			 */
			DPoint3d getEndPoint();

			/**
			 * @brief Destroy the Curve Graphic Properties object
			 * 
			 * @remark Needed for dynamic cast at least one virtual function
			 */
			virtual ~CurveGraphicProperties() {}; 

			/**
			 * @brief To String
			 * 
			 * @return string 
			 */
			string toString();
		};
	}
}