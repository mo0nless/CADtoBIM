#pragma once

/**
 * @file RuledSweepGraphicProperties.h
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
		 * @brief GraphicProperties Handle class for RuledSweep solid primitive
		 * 
		 * @remark This class inherits the SolidPrimitiveProperties class
		 * @see SolidPrimitiveProperties
		 */
		class RuledSweepGraphicProperties : public SolidPrimitiveProperties {

		private:
			vector<ShapesGraphicProperties*> mSectionCurvesVector;

		public:
			RuledSweepGraphicProperties();

			/**
			 * @brief Get the Section Curves Vector object
			 * 
			 * @return vector<ShapesGraphicProperties*> 
			 */
			vector<ShapesGraphicProperties*> getSectionCurvesVector();

			/**
			 * @brief Add a Section curve
			 * 
			 * @param newSectionCurve 
			 */
			void addSectionCurve(ShapesGraphicProperties* newSectionCurve);

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
		};
	}
}