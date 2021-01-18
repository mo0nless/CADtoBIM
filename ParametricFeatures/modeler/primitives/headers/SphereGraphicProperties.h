#pragma once

/**
 * @file SphereGraphicProperties.h
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
		 * @brief GraphicProperties Handle class for Sphere solid primitive
		 * 
		 * @remark This class inherits the SolidPrimitiveProperties class
		 * @see SolidPrimitiveProperties
		 */
		class SphereGraphicProperties : public SolidPrimitiveProperties {

		private:
			double _radius;

		public:
			SphereGraphicProperties();

			/**
			 * @brief Get the Radius object
			 * 
			 * @return double 
			 */
			double getRadius();

			/**
			 * @brief Set the Radius object
			 * 
			 * @param newadius 
			 */
			void setRadius(double newadius);

			string toString();
		};
	}
}