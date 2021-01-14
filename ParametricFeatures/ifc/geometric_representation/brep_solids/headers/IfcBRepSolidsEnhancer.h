#pragma once

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
		class IfcBRepSolidsEnhancer
		{
		public:
			IfcBRepSolidsEnhancer();

			void enhance(IfcHierarchyHelper<Ifc4>& file, SolidEntityGraphicProperties* solidEntityGraphicProperties, IfcElementBundle*& ifcElementBundle,
				IfcGraphicPropertiesBundle* ifcGraphicPropertiesBundle);

		private:
			Logging::Logger* _logger = Logging::Logger::getLogger();

			Ifc4::IfcGeometricRepresentationItem* buildBRepSolid(SolidEntityGraphicProperties* brepSolidsKernelEntity, IfcHierarchyHelper<Ifc4>& file, IfcGraphicPropertiesBundle* ifcGraphicPropertiesBundle);

			void processPolyfaceMesh(MeshTriangles* meshTriangles, IfcTemplatedEntityList<Ifc4::IfcFace>*& ifcFaceList);

			void buildSolidEntityEdgeLoop(SolidEntityGraphicProperties* brepSolidsKernelEntity, IfcGraphicPropertiesBundle* ifcGraphicPropertiesBundle, IfcHierarchyHelper<Ifc4>& file);

			void buildIfcFaceSurface(vector<GraphicProperties*> surfaceVectorGraphicProperties, IfcGraphicPropertiesBundle* ifcGraphicPropertiesBundle, IfcHierarchyHelper<Ifc4>& file, IfcEntityList*& entityList, IfcTemplatedEntityList<Ifc4::IfcFace>*& faceEntityList);

			template<class T>
			T searchOnMap(map<int, T>, int key);

			vector<EdgeIfcCurve*> solidEdges;

			mutable boost::shared_mutex _mutex;
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