#pragma once

/**
 * @file ArcGraphicProperties.h
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
		 * @brief GraphicProperties Handle class for Arc Curve
		 * 
		 * @remark This class inherits the CurveGraphicProperties class
		 * @see CurveGraphicProperties
		 */
		class ArcGraphicProperties : public CurveGraphicProperties
		{

		private:
			double mRadiusX;
			double mRadiusY;

			double mLength;

			double mSweepAngle;
			double mStartAngle;

			DVec3d mCenter;

			DVec3d mDirectionX;
			DVec3d mDirectionY;
			DVec3d mDirectionZ;

			bool mIsCircular;
			bool mIsFullEllipse;

		public:
			ArcGraphicProperties();
			
			/**
			 * @brief Set the Direction X Y object. Represent the XY plane the curve is laying on.
			 * 
			 * @param newDirectionX 
			 * @param newDirectionY 
			 */
			void setDirectionXY(DVec3d newDirectionX, DVec3d newDirectionY);

			/**
			 * @brief Get the Direction X object
			 * 
			 * @return DVec3d 
			 */
			DVec3d getDirectionX();

			/**
			 * @brief Get the Direction Y object
			 * 
			 * @return DVec3d 
			 */
			DVec3d getDirectionY();

			/**
			 * @brief Get the Direction Z object
			 * 
			 * @return DVec3d 
			 */
			DVec3d getDirectionZ();

			/**
			 * @brief Get the Is Circular object
			 * 
			 * @return true 
			 * @return false 
			 */
			bool getIsCircular();

			/**
			 * @brief Set the Is Circular object
			 * 
			 * @param value 
			 */
			void setIsCircular(bool value);

			/**
			 * @brief Get the Is Full Ellipse object
			 * 
			 * @return true 
			 * @return false 
			 */
			bool getIsFullEllipse();

			/**
			 * @brief Set the Is Full Ellipse object
			 * 
			 * @param value 
			 */
			void setIsFullEllipse(bool value);

			/**
			 * @brief Set the Length object
			 * 
			 * @param newLength 
			 */
			void setLength(double newLength);

			/**
			 * @brief Get the Length object
			 * 
			 * @return double 
			 */
			double getLength();

			/**
			 * @brief Set the Radius X Y object
			 * 
			 * @param newRadiusX 
			 * @param newRadiusY 
			 */
			void setRadiusXY(double newRadiusX, double newRadiusY);

			/**
			 * @brief Get the Radius X object
			 * 
			 * @return double 
			 */
			double getRadiusX();

			/**
			 * @brief Get the Radius Y object
			 * 
			 * @return double 
			 */
			double getRadiusY();

			/**
			 * @brief Set the Center Out object
			 * 
			 * @param newCenter 
			 */
			void setCenterOut(DPoint3d newCenter);

			/**
			 * @brief Get the Center Out object
			 * 
			 * @return DVec3d 
			 */
			DVec3d getCenterOut();

			/**
			 * @brief Set the Start Angle object
			 * 
			 * @param newStartAngle 
			 */
			void setStartAngle(double newStartAngle);

			/**
			 * @brief Get the Start Angle object
			 * 
			 * @return double 
			 */
			double getStartAngle();

			/**
			 * @brief Set the Sweep Angle object
			 * 
			 * @param newSweepAngle 
			 */
			void setSweepAngle(double newSweepAngle);

			/**
			 * @brief Get the Sweep Angle object
			 * 
			 * @return double 
			 */
			double getSweepAngle();
		};
	}
}