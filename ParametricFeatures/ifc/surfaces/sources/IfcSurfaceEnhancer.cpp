#include "..\headers\IfcSurfaceEnhancer.h"

void IfcSurfaceEnhancer::enhanceIfcSurface(vector<DictionaryProperties*>& dictionaryPropertiesVector, vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file)
{
	vector<Ifc4::IfcRepresentation*> ifcRepresentationVector;

	if (!dictionaryPropertiesVector.empty())
	{
		for (int i = 0; i < dictionaryPropertiesVector.size(); i++)
		{
			DictionaryProperties& dictionaryProperties = *dictionaryPropertiesVector.at(i);

			// TODO [MP] to be replaced with method to check by id. order doesnt guarantee that it's the correct element
			IfcElementBundle*& ifcElementBundle = ifcBundleVector.at(i);

			Ifc4::IfcRepresentationItem::list::ptr ifcTemplatedEntityList(new Ifc4::IfcRepresentationItem::list());

			for (auto element : dictionaryProperties.getElementBundle())
			{
				SolidPrimitiveProperties* solidPrimitiveProperties = dynamic_cast<SolidPrimitiveProperties*>(element->getGraphicProperties());
				if (solidPrimitiveProperties != nullptr) {
					Ifc4::IfcGeometricRepresentationItem* ifcRepresentationItem = buildIfcSurface(*solidPrimitiveProperties, file, element);
					if (ifcRepresentationItem != nullptr)
					{
						auto bundle = new IfcGraphicPropertiesBundle(element->getGraphicProperties(),
							ifcRepresentationItem, element->getElementHandle(), element->getElemDisplayParamsCP());
						bundle->setColor(element->getColor());
						bundle->setTransparency(element->getTransparency());
						ifcElementBundle->addIfcGraphicPropertiesBundle(bundle);
						//ifcTemplatedEntityList->push(ifcRepresentationItem);
					}
				}
			}
		}
	}
}

Ifc4::IfcGeometricRepresentationItem * IfcSurfaceEnhancer::buildIfcSurface(SolidPrimitiveProperties & primitiveGraphicProperties, IfcHierarchyHelper<Ifc4>& file, ElementBundle * elementBundle)
{
	
}
