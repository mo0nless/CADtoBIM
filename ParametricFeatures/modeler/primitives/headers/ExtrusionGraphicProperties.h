#pragma once

/**
 * @file ExtrusionGraphicProperties.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "SolidPrimitiveProperties.h"
#include "../../shapes/headers/ShapesGraphicProperties.h"

using namespace Modeler::Shapes;

using namespace Modeler::Primitives;

namespace Modeler
{
	namespace Primitives
	{
		/**
		 * @brief GraphicProperties Handle class for Extrusion solid primitive
		 * 
		 * @remark This class inherits the SolidPrimitiveProperties class
		 * @see SolidPrimitiveProperties
		 */
		class ExtrusionGraphicProperties : public SolidPrimitiveProperties {

		private:
			DVec3d _directionExtrusion;
			ShapesGraphicProperties* _shapesGraphicProperties;

			bool _isSolid;

		public:
			ExtrusionGraphicProperties();

			/**
			 * @brief Set the Direction Of Extrusion object
			 * 
			 * @param newDirection 
			 */
			void setDirectionOfExtrusion(DVec3d newDirection);

			/**
			 * @brief Get the Direction Of Extrusion object
			 * 
			 * @return DVec3d 
			 */
			DVec3d getDirectionOfExtrusion();

			/**
			 * @brief Set the Is Solid object
			 * 
			 * @param value 
			 */
			void setIsSolid(bool value);

			/**
			 * @brief Get the Is Solid object
			 * 
			 * @return true 
			 * @return false 
			 */
			bool getIsSolid();

			/**
			 * @brief Get the Legnth Of Extrusion object
			 * 
			 * @return double 
			 */
			double getLegnthOfExtrusion();

			/**
			 * @brief Get the Shapes Graphic Properties object
			 * 
			 * @return ShapesGraphicProperties* 
			 */
			ShapesGraphicProperties* getShapesGraphicProperties();

			/**
			 * @brief Set the Shapes Graphic Properties object
			 * 
			 * @param newShapesGraphicProperties 
			 */
			void setShapesGraphicProperties(ShapesGraphicProperties* newShapesGraphicProperties);

			string toString();

		};
	}
}