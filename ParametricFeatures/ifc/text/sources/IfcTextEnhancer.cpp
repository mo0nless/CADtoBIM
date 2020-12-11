#include "..\headers\IfcTextEnhancer.h"

IfcTextEnhancer::IfcTextEnhancer()
{
}

void IfcTextEnhancer::enhance(IfcHierarchyHelper<Ifc4>& file, TextGraphicProperties* textGraphicProperties, IfcElementBundle *& ifcElementBundle, GraphicGeomBundle * elementBundle)
{
	{
		_logger->logDebug(__FILE__, __LINE__, __func__);

		if (textGraphicProperties != nullptr) {
			Ifc4::IfcGeometricRepresentationItem* ifcRepresentationItem = buildTextString(textGraphicProperties, file, elementBundle);
			if (ifcRepresentationItem != nullptr)
			{
				auto bundle = new IfcGraphicPropertiesBundle(elementBundle->getGraphicProperties(),
					ifcRepresentationItem, elementBundle->getElementHandle());
				bundle->setColor(elementBundle->getColor());
				bundle->setTransparency(elementBundle->getTransparency());
				bundle->setMaterial(elementBundle->getMaterial());
				bundle->setLevelHandle(elementBundle->getLevelHandle());
				ifcElementBundle->addIfcGraphicPropertiesBundle(bundle);
			}
			else {
				_logger->logWarning(__FILE__, __LINE__, __func__, "ifcRepresentationItem IS NULL");
			}
		}

	}
}

Ifc4::IfcTextLiteralWithExtent * IfcTextEnhancer::buildTextString(TextGraphicProperties * textGraphicProperties, IfcHierarchyHelper<Ifc4>& file, GraphicGeomBundle * elementBundle)
{
	Ifc4::IfcPlanarExtent* planarExtent = new Ifc4::IfcPlanarExtent(textGraphicProperties->getHeight(), textGraphicProperties->getWidth());

	DVec3d centroid;
	centroid.Init(textGraphicProperties->getOrigin());

	Ifc4::IfcAxis2Placement3D* placement = IfcOperationsHelper::buildIfcAxis2Placement3D(
		centroid,
		textGraphicProperties->getVectorAxisZ(),
		textGraphicProperties->getVectorAxisX()
	);

	Ifc4::IfcTextLiteralWithExtent* txt = new Ifc4::IfcTextLiteralWithExtent(textGraphicProperties->getTextString(), placement, Ifc4::IfcTextPath::IfcTextPath_LEFT,planarExtent,"bottom-left");
	
	return txt;
}
