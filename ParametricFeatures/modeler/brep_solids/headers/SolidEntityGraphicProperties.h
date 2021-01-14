#pragma once

#include "TopologyStructures.h"
#include "../../surfaces/headers/MSBsplineSurfaceGraphicProperties.h"
#include "../../../common/utils/headers/BRepTypeEnumUtils.h"
#include "../../../common/enums/headers/BRepTypeEnum.h"

using namespace std;
using namespace Common::Utilities;
using namespace Common::Enums; 
using namespace Modeler::Surfaces;
using namespace Modeler::Properties;

namespace Modeler
{
	namespace BRepSolids
	{
		class SolidEntityGraphicProperties : public GraphicProperties
		{
		public:
			SolidEntityGraphicProperties();

			void addSolidOrSurfaceFace(GraphicProperties*& newFace);
			vector<GraphicProperties*> getSurfaceFacesVector();

			void addFaceBoundaryShape(ShapesGraphicProperties* bound);
			vector<ShapesGraphicProperties*> getSurfaceBoundaryShapes();

			void addMeshTriangulated(MeshTriangles* mesh);
			vector<MeshTriangles*> getMeshTriangulated();

			void setBRepTypeEnum(int solidBentleyType);
			BRepTypeEnum getBRepTypeEnum();

			vector<int> faceID;
			vector<vector<ShapesGraphicProperties*>> loopShapesBounds;

			bool meshProcessing = false;

		private:
			vector<ShapesGraphicProperties*> mFaceBoundaries;
			vector<GraphicProperties*> mBrepFaces;
			vector<MeshTriangles*> mMeshTriangulatedVector;
			vector<tuple<int, int>> mFaceIDVector;
			BRepTypeEnum mBRepType;
		};
	}
}

