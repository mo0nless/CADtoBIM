#pragma once

#include<tuple> // for tuple 
#include "../../../stdafx.h"
#include "../../../modeler/properties/headers/DictionaryProperties.h"
#include "../../../modeler/properties/brep_solids/headers/BRepGraphicProperties.h"
#include "../../../common/utils/headers/ShapesTypeEnumUtils.h"
#include "IfcBRepRelationship.h"

class IfcBRepSolidsEnhancer
{
public:
	IfcBRepSolidsEnhancer();

	void enhanceIfcBRepSolidsEnhancer(std::vector<DictionaryProperties*>& dictionaryPropertiesVector, std::vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file);
	
private:
	Ifc4::IfcGeometricRepresentationItem* buildGeometricRepresentationBsplineSurface(SolidEntityGraphicProperties* brepSolidsKernelEntity, IfcElementBundle*& ifcElementBundle, IfcHierarchyHelper<Ifc4>& file);
	Ifc4::IfcGeometricRepresentationItem* buildGeometricRepresentationFacetBrep(BRepGraphicProperties* brepSolidsKernelEntity, IfcElementBundle*& ifcElementBundle, IfcHierarchyHelper<Ifc4>& file);

	template<class T>
	T searchOnMap(std::map<int, T>, int key);
};

template<class T>
inline T IfcBRepSolidsEnhancer::searchOnMap(std::map<int, T> mappedValues, int key)
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
