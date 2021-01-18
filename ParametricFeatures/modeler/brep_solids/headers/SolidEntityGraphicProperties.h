#pragma once

/**
 * @file SolidEntityGraphicProperties.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "TopologyStructures.h"
#include "../../surfaces/headers/MSBsplineSurfaceGraphicProperties.h"
#include "../../../common/utils/headers/BRepTypeEnumUtils.h"
#include "../../../common/enums/headers/BRepTypeEnum.h"

using namespace std;
using namespace Common::Utilities;
using namespace Common::Enums; 
using namespace Modeler::Surfaces;
using namespace Modeler::Properties;
using namespace Modeler::Topology;

namespace Modeler
{
	namespace BRepSolids
	{
		/**
		 * @brief GraphicProperties Handle class for BRep Solid Entity
		 * 
		 * @remark This class inherits the GraphicProperties class
		 * @see GraphicProperties
		 */
		class SolidEntityGraphicProperties : public GraphicProperties
		{
		public:
			SolidEntityGraphicProperties();

			/**
			 * @brief Add a Solid Or Surface as a Face to the Entity
			 * 
			 * @param newFace the new graphic properties face
			 */
			void addSolidOrSurfaceFace(GraphicProperties*& newFace);

			/**
			 * @brief Get the Solid Or Surface Vector object
			 * 
			 * @return vector<GraphicProperties*> 
			 */
			vector<GraphicProperties*> getSolidOrSurfaceVector();

			/**
			 * @brief Add a face shape curve boundary 
			 * 
			 * @param bound the shape bounary
			 */
			void addFaceBoundaryShape(ShapesGraphicProperties* bound);

			/**
			 * @brief Get the Surface Boundaries Shapes Vector object 
			 * 
			 * @return vector<ShapesGraphicProperties*> 
			 */
			vector<ShapesGraphicProperties*> getSurfaceBoundaryShapes();

			/**
			 * @brief Add Mesh Triangulated to the entity
			 * 
			 * @param mesh the triangulated mesh
			 */
			void addMeshTriangulated(MeshTriangles* mesh);

			/**
			 * @brief Get the Mesh Triangulated Vector object
			 * 
			 * @return vector<MeshTriangles*> 
			 */
			vector<MeshTriangles*> getMeshTriangulated();

			/**
			 * @brief Set the entity type
			 * 
			 * @param solidBentleyType 
			 */
			void setBRepTypeEnum(int solidBentleyType);

			/**
			 * @brief Get the entity type
			 * 
			 * @return BRepTypeEnum 
			 */
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

