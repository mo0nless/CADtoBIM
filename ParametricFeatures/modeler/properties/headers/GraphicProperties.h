
#pragma once

/**
 * @file GraphicProperties.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <sstream>

#include <DgnPlatform/ElementGeometry.h>


using namespace std;

namespace Modeler
{
	namespace Properties
	{
		/**
		 * @brief Base Graphic Properties class for all the geometry
		 * 
		 */
		class GraphicProperties {

		private:

			double volume;
			double area;

			DPoint3d origin;
			DVec3d centroid;

			DVec3d vectorAxisX;
			DVec3d vectorAxisY;
			DVec3d vectorAxisZ;



		public:
			/**
			 * @brief Construct a new Graphic Properties object
			 * 
			 */
			GraphicProperties();
			virtual ~GraphicProperties() {}

			/**
			 * @brief Get the Area object
			 * 
			 * @return double 
			 */
			double getArea();

			/**
			 * @brief Set the Area object
			 * 
			 * @param newArea 
			 */
			void setArea(double newArea);
			
			/**
			 * @brief Get the Volume object
			 * 
			 * @return double 
			 */
			double getVolume();

			/**
			 * @brief Set the Volume object
			 * 
			 * @param newVolume 
			 */
			void setVolume(double newVolume);

			/**
			 * @brief Get the Centroid object
			 * 
			 * @return DVec3d 
			 */
			DVec3d getCentroid();

			/**
			 * @brief Set the Centroid object
			 * 
			 * @param newCentroid 
			 */
			void setCentroid(DVec3d newCentroid);

			/**
			 * @brief Get the Origin object
			 * 
			 * @return DPoint3d 
			 */
			DPoint3d getOrigin();

			/**
			 * @brief Set the Origin object
			 * 
			 * @param newOrigin 
			 */
			void setOrigin(DPoint3d newOrigin);

			/**
			 * @brief Set the Vector Axis X Y Z object
			 * 
			 * @param newVectorAxisX 
			 * @param newVectorAxisY 
			 * @param newVectorAxisZ 
			 */
			void setVectorAxis(DVec3d newVectorAxisX, DVec3d newVectorAxisY, DVec3d newVectorAxisZ);

			/**
			 * @brief Get the Vector Axis X object
			 * 
			 * @return DVec3d 
			 */
			DVec3d getVectorAxisX();

			/**
			 * @brief Get the Vector Axis Y object
			 * 
			 * @return DVec3d 
			 */
			DVec3d getVectorAxisY();

			/**
			 * @brief Get the Vector Axis Z object
			 * 
			 * @return DVec3d 
			 */
			DVec3d getVectorAxisZ();

			/**
			 * @brief Type of Geometry
			 * 
			 */
			IGeometry::GeometryType geometryType;
		};
	}
}