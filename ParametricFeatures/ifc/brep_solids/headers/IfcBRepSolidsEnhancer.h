#pragma once


#include "../../../stdafx.h"
#include "../../../modeler/properties/headers/DictionaryProperties.h"
#include "../../../modeler/properties/brep_solids/headers/BRepSolidsKernelEntity.h"
#include "../../../common/utils/headers/ShapesTypeEnumUtils.h"
#include "IfcBRepRelationship.h"

class IfcBRepSolidsEnhancer
{
public:
	IfcBRepSolidsEnhancer();

	void enhanceIfcBRepSolidsEnhancer(std::vector<DictionaryProperties*>& dictionaryPropertiesVector, std::vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file);
	
private:
	Ifc4::IfcGeometricRepresentationItem* buildGeometricRepresentationBsplineSurface(BRepSolidsKernelEntity* brepSolidsKernelEntity, IfcElementBundle*& ifcElementBundle, IfcHierarchyHelper<Ifc4>& file);
};

