#pragma once

#include "../../../stdafx.h"
#include "../../../modeler/properties/smart_feature/headers/SmartFeatureContainer.h"
#include "../../../modeler/properties/headers/DictionaryProperties.h"
#include "../../../common/utils/headers/NumberUtils.h"


class IfcDataHandler
{
public:
	//! @param[in] The Properties Dictionary vector that contais all the element graphics and properties parsed
	//! @param[in] SmartFeatureContainer which contains the properties related to the smart feature
	//! @remark This class taking care of calling the right class to process the graphic elements to the IFC
	IfcDataHandler(std::vector<DictionaryProperties*> dictProps, SmartFeatureContainer* smartContainer);

private:
	std::vector<DictionaryProperties*> dictionaryProperties;
	SmartFeatureContainer* smartFeatContainer;
	
	IfcHierarchyHelper<Ifc4>* file = nullptr;

	Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* PrimitivesMapperSwitch(SmartFeatureTreeNode& treeNode);
	Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* PrimitivesMapperSwitch(DictionaryProperties& dictionaryProp);

	Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* PrimitivesSolver(PrimitiveTypeEnum::PrimitiveTypeEnum primitiveType, GraphicProperties* graphicProperties);
	
	//! IfcTextSolver template method to map the selected format to string
	//! @param <IfcSchema> the standard selected.
	//! @remark The function needs to be placed here otherwise it will end up as an unresolved external symbol. More information at the address: https://stackoverflow.com/questions/456713/why-do-i-get-unresolved-external-symbol-errors-when-using-templates
	template<class IfcSchema>
	std::string IfcTextSolver();

};


template<class IfcSchema>
inline std::string IfcDataHandler::IfcTextSolver()
{
	if (std::is_same<IfcSchema, Ifc2x3>::value) return "IFC2X3";
	if (std::is_same<IfcSchema, Ifc4>::value) return "IFC4";
	if (std::is_same<IfcSchema, Ifc4x1>::value) return "IFC4X1";
	if (std::is_same<IfcSchema, Ifc4x2>::value) return "IFC4X2";
}