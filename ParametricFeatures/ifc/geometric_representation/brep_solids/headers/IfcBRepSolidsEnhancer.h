#pragma once

/**
 * @file IfcBRepSolidsEnhancer.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-20
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include<tuple> // for tuple 
#include "../../../../stdafx.h"
#include "../../../bundle/headers/IfcElementBundle.h"
#include "../../../../modeler/brep_solids/headers/SolidEntityGraphicProperties.h"
#include "../../../../modeler/primitives/headers/CylinderGraphicProperties.h"
#include "../../../../modeler/primitives/headers/ConeGraphicProperties.h"
#include "../../../../modeler/primitives/headers/BoxGraphicProperties.h"
#include "../../../../modeler/primitives/headers/SphereGraphicProperties.h"
#include "../../../../modeler/primitives/headers/TorusGraphicProperties.h"
#include "../../../../modeler/primitives/headers/RuledSweepGraphicProperties.h"
#include "../../../../modeler/brep_solids/headers/TopologyStructures.h"
#include "../../../../common/enums/headers/ShapesTypeEnum.h"
#include "../../shapes/headers/IfcShapesEnhancer.h"
#include "../../surfaces/headers/IfcSurfaceEnhancer.h"
#include "../../primitives/headers/IfcPrimitivesEnhancer.h"

using namespace Ifc::Bundle; 
using namespace Common::Enums;
using namespace Modeler::BRepSolids;
using namespace Modeler::Topology;

namespace Ifc
{
	namespace GeometricRepresentation
	{
		/**
		 * @brief Ifc BRep Solids Class Enhancer. Process the SolidEntityGraphicProperties to build BRep solid IFC representation
		 * 
		 * @remark the function is called by the class IfcBuilder
		 * @see IfcBuilder
		 */
		class IfcBRepSolidsEnhancer
		{
		public:
			IfcBRepSolidsEnhancer();
			
			/**
			 * @brief Enhancer that handle the processing process
			 * 
			 * @param file the Ifc file helper
			 * @param solidEntityGraphicProperties the BRep graphic properties
			 * @param ifcElementBundle the Element in which the BRep belongs
			 * @param ifcGraphicPropertiesBundle  the ifcGraphicPropertiesBundle 
			 */
			void enhance(IfcHierarchyHelper<Ifc4>& file, SolidEntityGraphicProperties* solidEntityGraphicProperties, IfcElementBundle*& ifcElementBundle,
				IfcGraphicPropertiesBundle* ifcGraphicPropertiesBundle);

		private:
			Logging::Logger* _logger = Logging::Logger::getLogger();

			/**
			 * @brief The builder of the IfcGeometricRepresentationItem BRep solid
			 * 
			 * @param solidEntityGraphicProperties 
			 * @param file 
			 * @param ifcGraphicPropertiesBundle 
			 * @return Ifc4::IfcGeometricRepresentationItem* 
			 */
			Ifc4::IfcGeometricRepresentationItem* buildBRepSolid(SolidEntityGraphicProperties* solidEntityGraphicProperties, IfcHierarchyHelper<Ifc4>& file, IfcGraphicPropertiesBundle* ifcGraphicPropertiesBundle);

			/**
			 * @brief 
			 * 
			 * @param meshTriangles the triangles faces
			 * @param ifcFaceList the list to fill with triangles Faces
			 */
			void processPolyfaceMesh(MeshTriangles* meshTriangles, IfcTemplatedEntityList<Ifc4::IfcFace>*& ifcFaceList);

			/**
			 * @brief Build and add the edges loop of the Brep Solid
			 * 
			 * @param solidEntityGraphicProperties 
			 * @param ifcGraphicPropertiesBundle 
			 * @param file 
			 */
			void buildSolidEntityEdgeLoop(SolidEntityGraphicProperties* solidEntityGraphicProperties, IfcGraphicPropertiesBundle* ifcGraphicPropertiesBundle, IfcHierarchyHelper<Ifc4>& file);

			/**
			 * @brief Build and add the Solids/Surfaces that compose the Brep Solid
			 * 
			 * @param surfaceVectorGraphicProperties  vector of Solids/Surfaces
			 * @param ifcGraphicPropertiesBundle 
			 * @param file 
			 * @param entityList 
			 * @param faceEntityList 
			 */
			void buildIfcFaceSurface(vector<GraphicProperties*> surfaceVectorGraphicProperties, IfcGraphicPropertiesBundle* ifcGraphicPropertiesBundle, IfcHierarchyHelper<Ifc4>& file, IfcEntityList*& entityList, IfcTemplatedEntityList<Ifc4::IfcFace>*& faceEntityList);

			template<class T>
			T searchOnMap(map<int, T>, int key);

			vector<EdgeIfcCurve*> solidEdges;
		};

		template<class T>
		inline T IfcBRepSolidsEnhancer::searchOnMap(map<int, T> mappedValues, int key)
		{
			for (auto const& element : mappedValues)
			{
				if (element.first == key)
				{
					return element.second;
				}
			}
			return NULL;
		}
	}
}