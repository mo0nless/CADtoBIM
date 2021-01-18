#pragma once

/**
 * @file RotationalSweepGraphicProperties.h
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
		 * @brief GraphicProperties Handle class for Rotational sweep solid primitive
		 * 
		 * @remark This class inherits the SolidPrimitiveProperties class
		 * @see SolidPrimitiveProperties
		 */
		class RotationalSweepGraphicProperties : public SolidPrimitiveProperties {

		private:
			double _radius;
			double _sweepRadians;
			DPoint3d _centerRotation;
			ShapesGraphicProperties* _shapesGraphicProperties;


		public:
			RotationalSweepGraphicProperties();

			//TODO[SB] make it private, create getter setter
			DVec3d rotationAxes, rotation;
			DRay3d axisOfRotation;

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

			/**
			 * @brief Get the Center Rotation object
			 * 
			 * @return DPoint3d 
			 */
			DPoint3d getCenterRotation();

			/**
			 * @brief Set the Center Rotation object
			 * 
			 * @param newCenterRotation 
			 */
			void setCenterRotation(DPoint3d newCenterRotation);

			string toString();
		};
	}
}