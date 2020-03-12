#pragma once

#include "../../../stdafx.h"
#include "../../../modeler/properties/headers/DictionaryProperties.h"

class IfcPrimitivesBuilder {

public:
	//void buildIfcPrimitives(std::vector<DictionaryProperties*>& dictionaryPropertiesVector);

	Ifc4::IfcRepresentationItem* buildIfcPrimitive(PrimitiveTypeEnum::PrimitiveTypeEnum primitiveType, GraphicProperties& graphicProperties, IfcHierarchyHelper<Ifc4>& file);

private:
	Ifc4::IfcRepresentationItem* buildBasicPrimitive(PrimitiveTypeEnum::PrimitiveTypeEnum primitiveTypeEnum, GraphicProperties& graphicProperties, Ifc4::IfcAxis2Placement3D * place, IfcHierarchyHelper<Ifc4>& file);
	Ifc4::IfcRepresentationItem* buildComplexPrimitive(PrimitiveTypeEnum::PrimitiveTypeEnum primitiveTypeEnum, GraphicProperties& graphicProperties, Ifc4::IfcAxis2Placement3D* place, IfcHierarchyHelper<Ifc4>& file);
	Ifc4::IfcAxis2Placement3D* buildIfcAxis2Placement3D(GraphicProperties& graphicProperties, IfcHierarchyHelper<Ifc4>& file);

};