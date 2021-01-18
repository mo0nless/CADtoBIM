#pragma once

/**
 * @file ShapesGraphicProperties.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-18
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../../curves/headers/CurveGraphicProperties.h"
#include "../../curves/headers/BsplineGraphicProperties.h"
#include "../../curves/headers/ArcGraphicProperties.h"
#include "../../curves/headers/InterpolationGraphicProperties.h"
#include "../../curves/headers/LineGraphicProperties.h"
#include "../../curves/headers/LineStringGraphicProperties.h"
#include "../../curves/headers/AkimaGraphicProperties.h"
#include "../../curves/headers/PointStringGraphicProperties.h"
#include "../../properties/headers/GraphicProperties.h"
#include <vector>

using namespace std;
using namespace Common;
using namespace Common::Enums;
using namespace Common::Utilities;
using namespace Modeler::Properties;
using namespace Modeler::Curves;

namespace Modeler
{
	namespace Shapes
	{
		/**
		 * @brief GraphicProperties Handle class for Shapes Curve Vector
		 * 
		 * @remark This class inherits the GraphicProperties class
		 * @see GraphicProperties
		 */
		class ShapesGraphicProperties : public GraphicProperties
		{
		public:
			/**
			 * @brief Construct a new Shapes Graphic Properties object
			 * 
			 */
			ShapesGraphicProperties();

			/**
			 * @brief Add Face Bound ID
			 * 
			 * @param newFaceidentifier 
			 */
			void addFaceBoundID(int newFaceidentifier);

			/**
			 * @brief Get the Faces Bound IDs 
			 * 
			 * @return vector<int> 
			 */
			vector<int> getFacesBoundIDs();

			/**
			 * @brief Set the Boundary Type Curve Vector Container object
			 * 
			 * @param boundaryBentleyType 
			 */
			void setBoundaryTypeCurvesContainer(int boundaryBentleyType);

			/**
			 * @brief Get the Boundary Type Curve Vector Container object
			 * 
			 * @return CurvesBoundaryTypeEnum 
			 */
			CurvesBoundaryTypeEnum getBoundaryTypeCurvesContainer();

			/**
			 * @brief Insert a new Curve Graphics Properties primitive 
			 * 
			 * @param newCurveGraphicProperties 
			 */
			void insertCurvesGraphicsProperties(CurveGraphicProperties* newCurveGraphicProperties);

			/**
			 * @brief Get the Curves Primitives Container Vector object
			 * 
			 * @return vector<CurveGraphicProperties*> 
			 */
			vector<CurveGraphicProperties*> getCurvesPrimitivesContainerVector();

			/**
			 * @brief Set the Is Filled Shape Curve vector object
			 * 
			 * @param value 
			 */
			void setIsFilled(bool value);

			/**
			 * @brief Get the Is Filled Shape Curve vector object
			 * 
			 * @return true 
			 * @return false 
			 */
			bool getIsFilled();

			/**
			 * @brief Get the Is Closed Shape Curve object
			 * 
			 * @return true 
			 * @return false 
			 */
			bool getIsClosed() const;

			/**
			 * @brief Set the Is Closed Shape Curve object
			 * 
			 * @param isClosed 
			 */
			void setIsClosed(bool isClosed);

			/**
			 * @brief Check if It is a Container Boundary with multiple Shape Curve vector
			 * 
			 * @return true 
			 * @return false 
			 */
			bool hasShapesGraphicsContainer() const;

			/**
			 * @brief Insert a new Shape Curve vector in the container
			 * 
			 * @param newShapesGraphicProperties 
			 */
			void insertShapesGraphicProperties(ShapesGraphicProperties* newShapesGraphicProperties);

			/**
			 * @brief Get the Container object with all the Shape Curve vector
			 * 
			 * @return vector<ShapesGraphicProperties*> 
			 */
			vector<ShapesGraphicProperties*> getShapesGraphicsContainer();

			/**
			 * @brief Get the Normal object
			 * 
			 * @return DVec3d 
			 */
			DVec3d getNormal() const;

			/**
			 * @brief Set the Normal object
			 * 
			 * @param normal 
			 */
			void setNormal(DVec3d normal);

			/**
			 * @brief Set the Start End Points object
			 * 
			 * @param start 
			 * @param end 
			 */
			void setStartEndPoints(DPoint3d start, DPoint3d end);

			/**
			 * @brief Get the Start Point object
			 * 
			 * @return DPoint3d 
			 */
			DPoint3d getStartPoint();

			/**
			 * @brief Get the End Point object
			 * 
			 * @return DPoint3d 
			 */
			DPoint3d getEndPoint();

			/**
			 * @brief Set the UV Start and End Points objects
			 * 
			 * @param sPoint UV start
			 * @param ePoint UV end
			 */
			void setUVstartEndPoints(DPoint3d sPoint, DPoint3d ePoint);

			/**
			 * @brief Get the UV Start Point object
			 * 
			 * @return DPoint3d 
			 */
			DPoint3d getUVstartPoint();

			/**
			 * @brief et the UV End Point object
			 * 
			 * @return DPoint3d 
			 */
			DPoint3d getUVendPoint();

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
			 * @brief Get the Has Single Curve object
			 * 
			 * @return true 
			 * @return false 
			 */
			bool getHasSingleCurve();

			/**
			 * @brief Set the Has Single Curve object
			 * 
			 * @param value 
			 */
			void setHasSingleCurve(bool value);
			

			virtual ~ShapesGraphicProperties();

			//TEMP
			string type = "";
			bool isPartOfLoop = false;

			string toString();

		private:
			vector<int> _faceBoundIdentifiers;

			int _nodeId;

			DVec3d _normal;

			DPoint3d mStartPoint;
			DPoint3d mEndPoint;
			DPoint3d mCentroid;

			DPoint3d mUVstartPoint;
			DPoint3d mUVendPoint;

			bool _isFilled;
			bool _isClosed;
			bool _hasShapesGraphicsContainer;
			bool _isSingleCurve;

			ShapesTypeEnum _curvesShapeTypeEnum;
			CurvesBoundaryTypeEnum _curvesBoundaryType;
			vector<CurveGraphicProperties*> _curvesPrimitivesContainer;
			vector<ShapesGraphicProperties*> _shapesGraphicsContainer;
		};
	}
}