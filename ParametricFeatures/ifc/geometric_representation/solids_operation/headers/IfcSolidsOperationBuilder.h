#pragma once

/**
 * @file IfcSolidsOperationBuilder.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../../../../stdafx.h"
#include "../../../../common/utils/headers/CreateSolidFunctionsEnumUtils.h"
#include "../../../../common/enums/headers/BooleanFunctionsEnum.h"
#include "../../../../modeler/properties/smart_feature/headers/SmartFeatureContainer.h"
#include "../../primitives/headers/IfcPrimitivesEnhancer.h"
#include "../../shapes/headers/IfcShapesEnhancer.h"
#include "../../../bundle/headers/IfcElementBundle.h"

using namespace Ifc::Bundle;
using namespace Ifc::GeometricRepresentation;
using namespace Common::Utilities;
using namespace Common::Enums;
using namespace Common;
using namespace Modeler::Properties;

namespace Ifc
{
	namespace GeometricRepresentation
	{
		/**
		 * @brief Class to handle the building of solids operation (Extrude, Thicken, Boolean, ...)
		 * 
		 * @remark the class is called and used by the SmartFeatureHandler Class
		 * @see SmartFeatureHandler
		 */
		class IfcSolidsOperationBuilder {

		public:
			/**
			 * @brief Build the IfcGeometricRepresentationItem with the correct solids operation (Extrude, Thicken, ...)
			 * 
			 * @param leftIfcRepresentationItem 
			 * @param rigthIfcRepresentationItem 
			 * @param ifcReaderPropertiesBundle 
			 * @param file 
			 * @return Ifc4::IfcGeometricRepresentationItem* 
			 */
			static Ifc4::IfcGeometricRepresentationItem* buildIfcCreateSolidsOperation(IfcElementBundle* leftIfcRepresentationItem, IfcElementBundle* rigthIfcRepresentationItem,
				IfcReaderPropertiesBundle& ifcReaderPropertiesBundle, IfcHierarchyHelper<Ifc4>& file);

			/**
			 * @brief Build the IfcGeometricRepresentationItem for boolean operation
			 * 
			 * @param leftIfcRepresentationItem 
			 * @param rigthIfcRepresentationItem 
			 * @param ifcReaderPropertiesBundle 
			 * @return Ifc4::IfcGeometricRepresentationItem* 
			 */
			static Ifc4::IfcGeometricRepresentationItem* solveBooleanOperation(Ifc4::IfcGeometricRepresentationItem* leftIfcRepresentationItem,
				Ifc4::IfcGeometricRepresentationItem* rigthIfcRepresentationItem, IfcReaderPropertiesBundle& ifcReaderPropertiesBundle);
		};
	}
}