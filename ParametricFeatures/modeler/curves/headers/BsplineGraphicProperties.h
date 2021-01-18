#pragma once

/**
 * @file BsplineGraphicProperties.h
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
		 * @brief GraphicProperties Handle class for BSpline Curve
		 * 
		 * @remark This class inherits the CurveGraphicProperties class
		 * @see CurveGraphicProperties
		 */
		class BsplineGraphicProperties : public CurveGraphicProperties
		{

		private:
			vector<double> mKnots;
			vector<int> mKnotsMultiplicity;

			int mNumberKnots;
			int mDegree;
			int mOrder;

			bool mIsClosed;
			bool mIsSelfIntersect;
			bool mKnotsValid;

		public:
			BsplineGraphicProperties();

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
			 * @brief Set the Is Closed object
			 * 
			 * @param newIsClosed 
			 */
			void setIsClosed(bool newIsClosed);

			/**
			 * @brief Get the Is C Losed object
			 * 
			 * @return true 
			 * @return false 
			 */
			bool getIsCLosed();

			/**
			 * @brief Set the Is Self Intersect object
			 * 
			 * @param newIsSelfIntersect 
			 */
			void setIsSelfIntersect(bool newIsSelfIntersect);

			/**
			 * @brief Get the Is Self Intersect object
			 * 
			 * @return true 
			 * @return false 
			 */
			bool getIsSelfIntersect();

			/**
			 * @brief Set the Knots object
			 * 
			 * @param newKnots 
			 */
			void setKnots(bvector<double> newKnots);

			/**
			 * @brief Get the Knots object
			 * 
			 * @return vector<double> 
			 */
			vector<double> getKnots();

			/**
			 * @brief Get the Number Knots object
			 * 
			 * @return int 
			 */
			int getNumberKnots();

			/**
			 * @brief Set the Are Knots Valid object
			 * 
			 * @param value 
			 */
			void setAreKnotsValid(bool value);

			/**
			 * @brief Get the Are Knots Valid object
			 * 
			 * @return true 
			 * @return false 
			 */
			bool getAreKnotsValid();

			/**
			 * @brief Set the Knots Multiplicity object
			 * 
			 * @param newMultiplicity 
			 */
			void setKnotsMultiplicity(bvector<size_t> newMultiplicity);

			/**
			 * @brief Get the Knots Multiplicity object
			 * 
			 * @return vector<int> 
			 */
			vector<int> getKnotsMultiplicity();
		};
	}
}