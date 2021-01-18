#pragma once

/**
 * @file BoxGraphicProperties.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include"SolidPrimitiveProperties.h"

using namespace Modeler::Primitives;

namespace Modeler
{
	namespace Primitives
	{
		/**
		 * @brief GraphicProperties Handle class for Box solid primitive
		 * 
		 * @remark This class inherits the SolidPrimitiveProperties class
		 * @see SolidPrimitiveProperties
		 */
		class BoxGraphicProperties : public SolidPrimitiveProperties {

		private:
			double _length;
			double _width;
			double _height;

		public:
			BoxGraphicProperties();

			/**
			 * @brief Get the Length object
			 * 
			 * @return double 
			 */
			double getLength();

			/**
			 * @brief Set the Length object
			 * 
			 * @param newLength 
			 */
			void setLength(double newLength);

			/**
			 * @brief Get the Width object
			 * 
			 * @return double 
			 */
			double getWidth();

			/**
			 * @brief Set the Width object
			 * 
			 * @param newWidth 
			 */
			void setWidth(double newWidth);

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
			 * @brief To String
			 * 
			 * @return string 
			 */
			string toString();
		};
	}
}