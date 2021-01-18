#pragma once

/**
 * @file LineStringGraphicProperties.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "CurveGraphicProperties.h"

using namespace Modeler::Curves;

namespace Modeler
{
	namespace Curves
	{
		/**
		 * @brief GraphicProperties Handle class for Line string Curve
		 * 
		 * @remark This class inherits the CurveGraphicProperties class
		 * @see CurveGraphicProperties
		 */
		class LineStringGraphicProperties : public CurveGraphicProperties
		{

		private:
			DPoint3d mDirectionTangent;
			int mNumSegment;

		public:
			LineStringGraphicProperties();

			/**
			 * @brief Set the Direction Tanget object
			 * 
			 * @param newDirTanget 
			 */
			void setDirectionTanget(DPoint3d newDirTanget);

			/**
			 * @brief Get the Direction Tangent object
			 * 
			 * @return DPoint3d 
			 */
			DPoint3d getDirectionTangent();

		};
	}
}