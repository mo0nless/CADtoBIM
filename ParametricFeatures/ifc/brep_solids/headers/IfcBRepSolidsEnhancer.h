#pragma once

#include<tuple> // for tuple 
#include "../../../stdafx.h"
//#include "../../headers/IfcElementBundle.h"
//#include "../../../modeler/properties/headers/DictionaryProperties.h"
#include "../../../modeler/brep_solids/headers/BRepGraphicProperties.h"
#include "../../../modeler/primitives/headers/CylinderGraphicProperties.h"
#include "../../../modeler/primitives/headers/ConeGraphicProperties.h"
#include "../../../modeler/primitives/headers/BoxGraphicProperties.h"
#include "../../../modeler/primitives/headers/SphereGraphicProperties.h"
#include "../../../modeler/primitives/headers/TorusGraphicProperties.h"
#include "../../../modeler/primitives/headers/RuledSweepGraphicProperties.h"
#include "../../../common/enums/headers/ShapesTypeEnum.h"
#include "../../shapes/headers/IfcShapesEnhancer.h"
#include "../../primitives/headers/IfcPrimitivesEnhancer.h"

struct EdgeIfcCurve
{
	Ifc4::IfcVertex* startVertex;
	Ifc4::IfcVertex* endVertex;
	Ifc4::IfcCartesianPoint* start;
	Ifc4::IfcCartesianPoint* end;
	Ifc4::IfcEdgeCurve* ifcEdgeCurve;
	Ifc4::IfcOrientedEdge* orientedEdge;
	vector<Ifc4::IfcOrientedEdge*> continuosOrientedEdges;
	bool isShared = false;
	vector<int> faceIDs;
	Ifc4::IfcEdgeLoop* edgeLoop;
	bool isSingleCurveClosedPath = false;

	DPoint3d startD3p, endD3p;
};

class IfcBRepSolidsEnhancer
{
public:
	IfcBRepSolidsEnhancer();

	void enhanceIfcBRepSolidsEnhancer(vector<DictionaryProperties*>& dictionaryPropertiesVector, vector<IfcElementBundle*>& ifcBundleVector,
		IfcHierarchyHelper<Ifc4>& file);
	
private:
	Ifc4::IfcGeometricRepresentationItem* buildGeometricRepresentationBsplineSurface(SolidEntityGraphicProperties* brepSolidsKernelEntity,
		IfcElementBundle*& ifcElementBundle, ElementBundle* elementBundle, IfcHierarchyHelper<Ifc4>& file);
	
	Ifc4::IfcGeometricRepresentationItem* buildGeometricRepresentationFacetBrep(BRepGraphicProperties* brepSolidsKernelEntity,
		IfcElementBundle*& ifcElementBundle, IfcHierarchyHelper<Ifc4>& file);

	void buildSolidEntityEdgeLoop(SolidEntityGraphicProperties* brepSolidsKernelEntity, ElementBundle* elementBundle, IfcHierarchyHelper<Ifc4>& file);

	void buildIfcSurface(vector<GraphicProperties*> surfaceVectorGraphicProperties, IfcElementBundle*& ifcElementBundle, 
		ElementBundle* elementBundle, IfcHierarchyHelper<Ifc4>& file, IfcEntityList*& entityList, IfcTemplatedEntityList<Ifc4::IfcFace>*& faceEntityList);

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
