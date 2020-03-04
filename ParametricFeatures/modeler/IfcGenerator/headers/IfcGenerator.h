#pragma once

#include "../../../stdafx.h"
#include "../../../modeler/properties/smart_feature/headers/SmartFeatureContainer.h"
#include "../../../modeler/properties/headers/DictionaryProperties.h"

/// @addtogroup IfcStandards
/// @beginGroup

/*=================================================================================**//**
* Class that allows to create IFC standards file and It's based on IfcOpenShell library.
* @see IfcOpenShell
* @bsiclass
+===============+===============+===============+===============+===============+======*/
class IfcGenerator
{
public:
	//! @param[in] The Properties Dictionary vector that contais all the element graphics and properties parsed
	//! @param[in] SmartFeatureContainer which contains the properties related to the smart feature
	//! @remark This class inherits and implement the Bentley IElementGraphicsProcessor Interface
	IfcGenerator(std::vector<DictionaryProperties*> dictProps, SmartFeatureContainer* smartContainer);

private:
	boost::none_t const null = boost::none;
	
	IfcHierarchyHelper<Ifc4> file = IfcHierarchyHelper<Ifc4>(IfcParse::schema_by_name("IFC4"));
	std::vector<DictionaryProperties*> dictionaryProperties;	
	std::stack <SmartFeatureTreeNode*> stackSmartFeature;
	SmartFeatureContainer* smartFeatContainer;


	Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* PrimitivesMapperSwitch(SmartFeatureTreeNode* treeNode);
	void ReverseLevelOrder();
	void SmartFeatureBooleanOperations();

	//! IfcTextSolver template method to map the selected format to string
	//! @param <IfcSchema> the standard selected.
	//! @remark The function needs to be placed here otherwise it will end up as an unresolved external symbol. More information at the address: https://stackoverflow.com/questions/456713/why-do-i-get-unresolved-external-symbol-errors-when-using-templates
	template<class IfcSchema>
	std::string IfcTextSolver();


};


template<class IfcSchema>
inline std::string IfcGenerator::IfcTextSolver()
{
	if (std::is_same<IfcSchema, Ifc2x3>::value) return "IFC2X3";
	if (std::is_same<IfcSchema, Ifc4>::value) return "IFC4";
	if (std::is_same<IfcSchema, Ifc4x1>::value) return "IFC4X1";
	if (std::is_same<IfcSchema, Ifc4x2>::value) return "IFC4X2";
}
/// @endGroup

