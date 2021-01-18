#pragma once

/**
 * @file InterpolationGraphicProperties.h
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
		 * @brief GraphicProperties Handle class for Interpolation Curve
		 * 
		 * @remark This class inherits the CurveGraphicProperties class
		 * @see CurveGraphicProperties
		 */
		class InterpolationGraphicProperties : public CurveGraphicProperties
		{

		private:
			int mDegree;
			int mOrder;
			bool mIsPeriodic;

		public:
			InterpolationGraphicProperties();

			/**
			 * @brief Set the Order object
			 * 
			 * @param newOrder 
			 */
			void setOrder(size_t newOrder);

			/**
			 * @brief Get the Order object
			 * 
			 * @return int 
			 */
			int getOrder();

			/**
			 * @brief Get the Degree object
			 * 
			 * @return int 
			 */
			int getDegree();

			/**
			 * @brief Set the Is Periodic object
			 * 
			 * @param newIsPeriodic 
			 */
			void setIsPeriodic(bool newIsPeriodic);

			/**
			 * @brief Get the Is Periodic object
			 * 
			 * @return true 
			 * @return false 
			 */
			bool getIsPeriodic();
		};
	}
}