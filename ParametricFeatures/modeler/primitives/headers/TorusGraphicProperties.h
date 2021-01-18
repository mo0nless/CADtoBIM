#pragma once

/**
 * @file TorusGraphicProperties.h
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
		 * @brief GraphicProperties Handle class for Torus solid primitive
		 * 
		 * @remark This class inherits the SolidPrimitiveProperties class
		 * @see SolidPrimitiveProperties
		 */
		class TorusGraphicProperties : public SolidPrimitiveProperties {

		private:
			double _minorRadius;
			double _majorRadius;
			double _sweepRadians;
			DPoint3d _centerPointOfRotation;

		public:
			TorusGraphicProperties();

			/**
			 * @brief Get the Minor Radius object
			 * 
			 * @return double 
			 */
			double getMinorRadius();

			/**
			 * @brief Set the Minor Radius object
			 * 
			 * @param newMinorRadius 
			 */
			void setMinorRadius(double newMinorRadius);

			/**
			 * @brief Get the Major Radius object
			 * 
			 * @return double 
			 */
			double getMajorRadius();

			/**
			 * @brief Set the Major Radius object
			 * 
			 * @param newMajorRadius 
			 */
			void setMajorRadius(double newMajorRadius);

			/**
			 * @brief Get the Sweep Radians object
			 * 
			 * @return double 
			 */
			double getSweepRadians();

			/**
			 * @brief Set the Sweep Radians object
			 * 
			 * @param newSweepRadians 
			 */
			void setSweepRadians(double newSweepRadians);

			/**
			 * @brief Get the Center Point Of Rotation object
			 * 
			 * @return DPoint3d 
			 */
			DPoint3d getCenterPointOfRotation();

			/**
			 * @brief Set the Center Point Of Rotation object
			 * 
			 * @param newCenterPointOfRotation 
			 */
			void setCenterPointOfRotation(DPoint3d newCenterPointOfRotation);

			string toString();
		};
	}
}