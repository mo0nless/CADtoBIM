#pragma once

/**
 * @file MSBsplineSurfaceGraphicProperties.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../../shapes/headers/ShapesGraphicProperties.h"
#include <DgnPlatform/ElementGeometry.h>
#include "../../properties/headers/GraphicProperties.h"
#include <vector>

using namespace std;
using namespace Modeler::Shapes;
using namespace Modeler::Properties;

namespace Modeler
{
	namespace Surfaces
	{
		/**
		 * @brief GraphicProperties Handle class for BSpilne Surface solid primitive
		 * 
		 * @remark This class inherits the GraphicProperties class
		 * @see GraphicProperties
		 */
		class MSBsplineSurfaceGraphicProperties : public GraphicProperties
		{
		public:
			MSBsplineSurfaceGraphicProperties();

			/**
			 * @brief Set the Control Points object
			 * 
			 * @param newControlPoints 
			 * @param numU 
			 * @param numV 
			 */
			void setControlPoints(vector<vector<DPoint3d>> newControlPoints, int numU, int numV);

			/**
			 * @brief Get the Control Points object
			 * 
			 * @return vector<vector<DPoint3d>> 
			 */
			vector<vector<DPoint3d>> getControlPoints();

			/**
			 * @brief Get the Num U Poles object
			 * 
			 * @return int 
			 */
			int getNumUPoles();

			/**
			 * @brief Get the Num V Poles object
			 * 
			 * @return int 
			 */
			int getNumVPoles();

			/**
			 * @brief Set UV Order
			 * 
			 * @param newUOrder 
			 * @param newVOrder 
			 */
			void setUVOrder(size_t newUOrder, size_t newVOrder);

			/**
			 * @brief Get U Order
			 * 
			 * @return int 
			 */
			int getUOrder();

			/**
			 * @brief Get V Order
			 * 
			 * @return int 
			 */
			int getVOrder();

			/**
			 * @brief Get U Degree
			 * 
			 * @return int 
			 */
			int getUDegree();

			/**
			 * @brief Get V Degree
			 * 
			 * @return int 
			 */
			int getVDegree();

			/**
			 * @brief Set UV is closed 
			 * 
			 * @param newUIsClosed 
			 * @param newVIsClosed 
			 */
			void setUVIsClosed(bool newUIsClosed, bool newVIsClosed);

			/**
			 * @brief Get U is closed 
			 * 
			 * @return true 
			 * @return false 
			 */
			bool getUIsCLosed();

			/**
			 * @brief Get V is closed 
			 * 
			 * @return true 
			 * @return false 
			 */
			bool getVIsCLosed();

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
			 * @brief Set UV Knots
			 * 
			 * @param newUKnots 
			 * @param newVKnots 
			 */
			void setUVKnots(bvector<double> newUKnots, bvector<double> newVKnots);

			/**
			 * @brief Get U Knots
			 * 
			 * @return vector<double> 
			 */
			vector<double> getUKnots();

			/**
			 * @brief Get V Knots
			 * 
			 * @return vector<double> 
			 */
			vector<double> getVKnots();

			/**
			 * @brief Set UV Knots Multiplicity
			 * 
			 * @param newUMultiplicity 
			 * @param newVMultiplicity 
			 */
			void setUVKnotsMultiplicity(bvector<size_t> newUMultiplicity, bvector<size_t> newVMultiplicity);
			
			/**
			 * @brief Get U Knots Multiplicity
			 * 
			 * @return vector<int> 
			 */
			vector<int> getUKnotsMultiplicity();

			/**
			 * @brief Get V Knots Multiplicity
			 * 
			 * @return vector<int> 
			 */
			vector<int> getVKnotsMultiplicity();

			/**
			 * @brief Set the Weights object
			 * 
			 * @param newWeights 
			 */
			void setWeights(vector<vector<double>> newWeights);

			/**
			 * @brief Get the Weights object
			 * 
			 * @return vector<vector<double>> 
			 */
			vector<vector<double>> getWeights();

			/**
			 * @brief Set the Bentley Struct Face Id object
			 * 
			 * @param id 
			 */
			void setFaceId(FaceId id);

			/**
			 * @brief Get Bentley Struct Face ID object
			 * 
			 * @return FaceId 
			 */
			FaceId getBFaceId();

			/**
			 * @brief Set the Face Id object
			 * 
			 * @param id 
			 */
			void setFaceId(int id);

			/**
			 * @brief Get the Face Id object
			 * 
			 * @return int 
			 */
			int getFaceId();

			/**
			 * @brief Set the Node Id object
			 * 
			 * @param id 
			 */
			void setNodeId(int id);

			/**
			 * @brief Get the Node Id object
			 * 
			 * @return int 
			 */
			int getNodeId();

			/**
			 * @brief Set the Number Of Bounds object
			 * 
			 * @param num 
			 */
			void setNumberOfBounds(int num);

			/**
			 * @brief Get the Number Of Bounds object
			 * 
			 * @return int 
			 */
			int getNumberOfBounds();

			/**
			 * @brief Set the Bounds Vector Points object
			 * 
			 * @param bounds 
			 */
			void setBoundsVectorPoints(vector<vector<DPoint3d>> bounds);

			/**
			 * @brief Get the Bounds Vector Points object
			 * 
			 * @return vector<vector<DPoint3d>> 
			 */
			vector<vector<DPoint3d>> getBoundsVectorPoints();

			/**
			 * @brief Add the Surface Boundary Shape object
			 * 
			 * @param bound 
			 */
			void addSurfaceBoundaryShape(ShapesGraphicProperties* bound);

			/**
			 * @brief Get the Surface Boundary Shape object
			 * 
			 * @return ShapesGraphicProperties* 
			 */
			ShapesGraphicProperties* getSurfaceBoundaryShape();

			//TODO [SB] Create getter setter function
			bool hasValidWeights;
			bool hasValidKnots;

		private:
			vector<vector<DPoint3d>> mControlPoints;
			vector<vector<DPoint3d>> mBoundsVectorPoints;

			int mNumberOfBounds;
			int mFaceId;
			int mNodeId;
			FaceId mBentleyFaceId;

			vector<vector<double>> mWeigths;
			vector<double> mUKnots;
			vector<double> mVKnots;

			vector<int> mUKnotsMultiplicity;
			vector<int> mVKnotsMultiplicity;

			ShapesGraphicProperties* mSurfaceBoundary;

			int mNumUPoles;
			int mNumVPoles;

			int mUDegree;
			int mVDegree;

			int mUOrder;
			int mVOrder;

			bool mUIsClosed;
			bool mVIsClosed;

			bool mIsSelfIntersect;
		};
	}
}


