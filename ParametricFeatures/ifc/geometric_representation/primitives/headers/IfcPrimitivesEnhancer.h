#pragma once

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

namespace Ifc
{
	namespace GeometricRepresentation
	{
		class IfcPrimitivesEnhancer {

		public:
			void enhance(IfcHierarchyHelper<Ifc4>& file, SolidPrimitiveProperties* solidPrimitiveProperties, IfcElementBundle* ifcElementBundle,
				IfcGraphicPropertiesBundle* ifcGraphicPropertiesBundle);
			Ifc4::IfcGeometricRepresentationItem* buildIfcPrimitive(SolidPrimitiveProperties& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file,
				IfcGraphicPropertiesBundle* ifcGraphicPropertiesBundle);
		private:
			Logging::Logger* _logger = Logging::Logger::getLogger();

			mutable boost::shared_mutex _mutex;

			Ifc4::IfcCsgSolid* buildBasicPrimitive(SolidPrimitiveProperties& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file);
			Ifc4::IfcGeometricRepresentationItem* buildComplexPrimitive(SolidPrimitiveProperties& primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file,
				IfcGraphicPropertiesBundle* ifcGraphicPropertiesBundle);
		};
	}
}