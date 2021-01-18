#pragma once

/**
 * @file CylinderGraphicProperties.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "SolidPrimitiveProperties.h"

using namespace Modeler::Primitives;

namespace Modeler
{
	namespace Primitives
	{
		/**
		 * @brief GraphicProperties Handle class for Cylinder solid primitive
		 * 
		 * @remark This class inherits the SolidPrimitiveProperties class
		 * @see SolidPrimitiveProperties
		 */
		class CylinderGraphicProperties :public SolidPrimitiveProperties {

		private:
			double _radius;
			double _height;
			DPoint3d _baseOrigin;

		public:
			CylinderGraphicProperties();

			/**
			 * @brief Get the Radius object
			 * 
			 * @return double 
			 */
			double getRadius();

			/**
			 * @brief Set the Radius object
			 * 
			 * @param newRadius 
			 */
			void setRadius(double newRadius);

			/**
			 * @brief Get the Height object
			 * 
			 * @return double 
			 */
			double getHeight();

			/**
			 * @brief Set the Height object
			 * 
			 * @param newHeight 
			 */
			void setHeight(double newHeight);

			/**
			 * @brief Get the Base Origin object
			 * 
			 * @return DPoint3d 
			 */
			DPoint3d getBaseOrigin();

			/**
			 * @brief Set the Base Origin object
			 * 
			 * @param newBaseOrigin 
			 */
			void setBaseOrigin(DPoint3d newBaseOrigin);

			string toString();
		};
	}
}