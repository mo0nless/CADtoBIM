#pragma once

/**
 * @file IfcPrimitivesEnhancer.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-21
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../../../../stdafx.h"
#include "../../../../common/utils/headers/NumberUtils.h"
#include "../../../../modeler/primitives/headers/SolidPrimitiveProperties.h"
#include "../../../../modeler/primitives/headers/CylinderGraphicProperties.h"
#include "../../../../modeler/primitives/headers/ConeGraphicProperties.h"
#include "../../../../modeler/primitives/headers/BoxGraphicProperties.h"
#include "../../../../modeler/primitives/headers/SphereGraphicProperties.h"
#include "../../../../modeler/primitives/headers/TorusGraphicProperties.h"
#include "../../../../modeler/primitives/headers/RotationalSweepGraphicProperties.h"
#include "../../../../modeler/primitives/headers/RuledSweepGraphicProperties.h"
#include "../../../../modeler/primitives/headers/ExtrusionGraphicProperties.h"
#include "../../../../common/enums/headers/ShapesTypeEnum.h"
#include "../../../bundle/headers/IfcElementBundle.h"
#include "../../shapes/headers/IfcShapesEnhancer.h"

#include "../../../../common/models/headers/SessionManager.h"

using namespace Ifc::Bundle;
using namespace Common::Utilities;
using namespace Common::Models;
using namespace Common::Enums; 
using namespace Modeler::Primitives;

namespace Ifc
{
	namespace GeometricRepresentation
	{
		/**
		 * @brief Ifc Primitives Class Enhancer. Process the SolidEntityGraphicProperties to build CSG Primitives solid IFC representation
		 * 
		 * @remark the function is called by the class IfcBuilder
		 * @see IfcBuilder
		 */
		class IfcPrimitivesEnhancer {

		public:
			/**
			 * @brief Enhancer that handle the processing process
			 * 
			 * @param file the Ifc file helper
			 * @param solidPrimitiveProperties the Primitives solid graphic properties
			 * @param ifcElementBundle the Element in which the Primitives solid belongs
			 * @param ifcGraphicPropertiesBundle  the ifcGraphicPropertiesBundle 
			 */
			void enhance(IfcHierarchyHelper<Ifc4>& file, SolidPrimitiveProperties* solidPrimitiveProperties, IfcElementBundle* ifcElementBundle,
				IfcGraphicPropertiesBundle* ifcGraphicPropertiesBundle);
			
			/**
			 * @brief The builder of the IfcGeometricRepresentationItem CSG Primitives solid
			 * 
			 * @param primitiveGraphicProperties 
			 * @param file 
			 * @param ifcGraphicPropertiesBundle 
			 * @return Ifc4::IfcGeometricRepresentationItem* 
			 */
			Ifc4::IfcGeometricRepresentationItem* buildIfcPrimitive(SolidPrimitiveProperties& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file,
				IfcGraphicPropertiesBundle* ifcGraphicPropertiesBundle);
		private:
			Logging::Logger* _logger = Logging::Logger::getLogger();

			/**
			 * @brief Build a Basic Primitive solid
			 * 
			 * @param primitiveGraphicProperties 
			 * @param file 
			 * @return Ifc4::IfcCsgSolid* 
			 */
			Ifc4::IfcCsgSolid* buildBasicPrimitive(SolidPrimitiveProperties& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file);

			/**
			 * @brief Build an advanced Primitive solid
			 * 
			 * @param primitiveGraphicProperties 
			 * @param file 
			 * @param ifcGraphicPropertiesBundle 
			 * @return Ifc4::IfcGeometricRepresentationItem* 
			 */
			Ifc4::IfcGeometricRepresentationItem* buildComplexPrimitive(SolidPrimitiveProperties& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file,
				IfcGraphicPropertiesBundle* ifcGraphicPropertiesBundle);
		};
	}
}