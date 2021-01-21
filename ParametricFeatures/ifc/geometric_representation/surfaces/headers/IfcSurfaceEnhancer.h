#pragma once
/**
 * @file IfcSurfaceEnhancer.h
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
#include "../../../../modeler/surfaces/headers/MSBsplineSurfaceGraphicProperties.h"
#include "../../../../common/enums/headers/ShapesTypeEnum.h"
#include "../../../bundle/headers/IfcElementBundle.h"
#include "../../shapes/headers/IfcShapesEnhancer.h"


using namespace std;
using namespace Ifc::Bundle;
using namespace Ifc::GeometricRepresentation;
using namespace Common::Utilities;
using namespace Common::Enums;
using namespace Modeler::Primitives;
using namespace Modeler::Surfaces;

namespace Ifc
{
	namespace GeometricRepresentation
	{
		/**
		 * @brief Ifc Surface Class Enhancer. Process the MSBsplineSurface GraphicProperties to build BSpline Surface IFC representation
		 * 
		 * @remark the function is called by the class IfcBuilder
		 * @see IfcBuilder
		 */
		class IfcSurfaceEnhancer
		{

		public:
			/**
			 * @brief Enhancer that handle the processing process
			 * 
			 * @param file the Ifc file helper
			 * @param msBsplineSurfaceGraphicProperties the BSpline Surface graphic properties
			 * @param ifcElementBundle the Element in which the BSpline Surface belongs
			 * @param ifcGraphicPropertiesBundle  the ifcGraphicPropertiesBundle 
			 */
			void enhance(IfcHierarchyHelper<Ifc4>& file, MSBsplineSurfaceGraphicProperties* msBsplineSurfaceGraphicProperties, IfcElementBundle*& ifcElementBundle,
				IfcGraphicPropertiesBundle* ifcGraphicPropertiesBundle, bool addToIfcElementBundle = true);

			/**
			 * @brief Builde the correct IfcBSplineSurface 
			 * 
			 * @param msBsplineSurfaceGraphicProperties 
			 * @param file 
			 * @param ifcGraphicPropertiesBundle 
			 * @return Ifc4::IfcBSplineSurface* 
			 */
			Ifc4::IfcBSplineSurface* buildIfcSurface(MSBsplineSurfaceGraphicProperties& msBsplineSurfaceGraphicProperties, IfcHierarchyHelper<Ifc4>& file, IfcGraphicPropertiesBundle* ifcGraphicPropertiesBundle);
		private:
			Logging::Logger* _logger = Logging::Logger::getLogger();
		};
	}
}