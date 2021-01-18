#pragma once

/**
 * @file LineGraphicProperties.h
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
		 * @brief GraphicProperties Handle class for Line Curve
		 * 
		 * @remark This class inherits the CurveGraphicProperties class
		 * @see CurveGraphicProperties
		 */
		class LineGraphicProperties : public CurveGraphicProperties
		{

		private:
			DVec3d mDirectionTangent;

		public:
			LineGraphicProperties();

			/**
			 * @brief Set the Direction Tanget object
			 * 
			 * @param newDirTanget 
			 */
			void setDirectionTanget(DVec3d newDirTanget);

			/**
			 * @brief Get the Direction Tangent object
			 * 
			 * @return DVec3d 
			 */
			DVec3d getDirectionTangent();
		};
	}
}