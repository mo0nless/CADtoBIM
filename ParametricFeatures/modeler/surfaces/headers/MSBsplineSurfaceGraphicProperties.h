#pragma once

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
		class MSBsplineSurfaceGraphicProperties : public GraphicProperties
		{
		public:
			MSBsplineSurfaceGraphicProperties();

			void setControlPoints(vector<vector<DPoint3d>> newControlPoints, int numU, int numV);
			vector<vector<DPoint3d>> getControlPoints();

			int getNumUPoles();
			int getNumVPoles();

			void setUVOrder(size_t newUOrder, size_t newVOrder);
			int getUOrder();
			int getVOrder();

			int getUDegree();
			int getVDegree();

			void setUVIsClosed(bool newUIsClosed, bool newVIsClosed);
			bool getUIsCLosed();
			bool getVIsCLosed();

			void setIsSelfIntersect(bool newIsSelfIntersect);
			bool getIsSelfIntersect();

			void setUVKnots(bvector<double> newUKnots, bvector<double> newVKnots);
			vector<double> getUKnots();
			vector<double> getVKnots();

			void setUVKnotsMultiplicity(bvector<size_t> newUMultiplicity, bvector<size_t> newVMultiplicity);
			vector<int> getUKnotsMultiplicity();
			vector<int> getVKnotsMultiplicity();

			void setWeights(vector<vector<double>> newWeights);
			vector<vector<double>> getWeights();

			void setFaceId(FaceId id);
			FaceId getBFaceId();

			void setFaceId(int id);
			int getFaceId();

			void setNodeId(int id);
			int getNodeId();

			void setNumberOfBounds(int num);
			int getNumberOfBounds();

			void setBoundsVectorPoints(vector<vector<DPoint3d>> bounds);
			vector<vector<DPoint3d>> getBoundsVectorPoints();

			void addSurfaceBoundaryShape(ShapesGraphicProperties* bound);
			ShapesGraphicProperties* getSurfaceBoundaryShape();

			//TODO [SB] Create get function
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


