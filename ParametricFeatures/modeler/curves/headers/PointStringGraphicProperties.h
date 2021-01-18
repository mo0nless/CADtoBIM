#pragma once

/**
 * @file PointStringGraphicProperties.h
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
		 * @brief GraphicProperties Handle class for Point string
		 * 
		 * @remark This class inherits the CurveGraphicProperties class
		 * @see CurveGraphicProperties
		 */
		class PointStringGraphicProperties : public CurveGraphicProperties
		{

		private:
			bool mIsPort = true;

		public:
			PointStringGraphicProperties();

			/**
			 * @brief Get the Is Port object
			 * 
			 * @return true 
			 * @return false 
			 */
			bool getIsPort();

			/**
			 * @brief Set the Is Port object
			 * 
			 * @param value 
			 */
			void setIsPort(bool value);
		};
	}
}
