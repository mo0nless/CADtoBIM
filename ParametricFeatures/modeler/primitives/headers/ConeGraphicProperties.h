#pragma once

/**
 * @file ConeGraphicProperties.h
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
		 * @brief GraphicProperties Handle class for Cone solid primitive
		 * 
		 * @remark This class inherits the SolidPrimitiveProperties class
		 * @see SolidPrimitiveProperties
		 */
		class ConeGraphicProperties : public SolidPrimitiveProperties {

		private:
			double _baseRadius;
			double _topRadius;
			double _height;
			DPoint3d _topOrigin;
			DPoint3d _baseOrigin;

		public:
			/**
			 * @brief Construct a new Cone Graphic Properties object
			 * 
			 * @param primitiveTypeEnum tthe type
			 */
			ConeGraphicProperties(PrimitiveTypeEnum primitiveTypeEnum);

			/**
			 * @brief Get the Base Radius object
			 * 
			 * @return double 
			 */
			double getBaseRadius();

			/**
			 * @brief Set the Base Radius object
			 * 
			 * @param newBaseRadius 
			 */
			void setBaseRadius(double newBaseRadius);

			/**
			 * @brief Get the Top Radius object
			 * 
			 * @return double 
			 */
			double getTopRadius();

			/**
			 * @brief Set the Top Radius object
			 * 
			 * @param newTopRadius 
			 */
			void setTopRadius(double newTopRadius);

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
			 * @brief Get the Top Origin object
			 * 
			 * @return DPoint3d 
			 */
			DPoint3d getTopOrigin();

			/**
			 * @brief Set the Top Origin object
			 * 
			 * @param newTopOrigin 
			 */
			void setTopOrigin(DPoint3d newTopOrigin);

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