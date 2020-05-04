#include "../headers/IfcElementBuilder.h"

IfcElementBuilder::IfcElementBuilder()
{
}

void IfcElementBuilder::processIfcElement(std::vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file)
{
	//Create the vector for the distribution element 
	//std::vector<IfcElementBundle*>ifcDistributionBundleVector;
	for (auto& ifcElementBundle : ifcBundleVector) //const& removed
	{
		Ifc4::IfcRepresentationItem::list::ptr ifcRepresentationItemList(new Ifc4::IfcRepresentationItem::list());

		for (auto const& ifcGraphicPropertiesBundle : ifcElementBundle->getIfcGraphicPropertiesBundleVector()) {

			if (ifcGraphicPropertiesBundle->getIfcRepresentationItem() != nullptr && ifcGraphicPropertiesBundle->getShow()) {
				ifcRepresentationItemList->push(ifcGraphicPropertiesBundle->getIfcRepresentationItem());
			}
		}

		if (ifcRepresentationItemList->size() < 1) {
			continue;
		}

		Ifc4::IfcRepresentation* ifcRepresentation = new Ifc4::Ifc4::IfcRepresentation(file.getSingle<Ifc4::IfcGeometricRepresentationContext>(),
			ifcElementBundle->getModelerElementDescriptor(), ifcElementBundle->getModelerElementDescriptor(), ifcRepresentationItemList);

		Ifc4::IfcRepresentation::list::ptr ifcRepresentationList(new Ifc4::IfcRepresentation::list());
		ifcRepresentationList->push(ifcRepresentation);

		Ifc4::IfcProductDefinitionShape* shape = new Ifc4::IfcProductDefinitionShape(boost::none, boost::none, ifcRepresentationList);

		file.addEntity(shape);

		if (ifcElementBundle->getHasElementConnection())
		{
			//ifcDistributionBundleVector.push_back(ifcElementBundle);
			Ifc4::IfcDistributionElement * ifcDistributionElem = buildIfcDistributionElement(ifcElementBundle, shape, file);
			file.addBuildingProduct(ifcDistributionElem);

			//Set the element to the IfcElementBundle
			ifcElementBundle->setIfcElement(ifcDistributionElem);
		}
		else
		{
			Ifc4::IfcElement* ifcElement = buildIfcElement(ifcElementBundle, shape, file);
			file.addBuildingProduct(ifcElement);

			//Set the element to the IfcElementBundle
			ifcElementBundle->setIfcElement(ifcElement);
		}

	}
}

Ifc4::IfcElement * IfcElementBuilder::buildIfcElement(IfcElementBundle *& ifcElementBundle, Ifc4::IfcProductDefinitionShape * elemShape, IfcHierarchyHelper<Ifc4>& file)
{
	Ifc4::IfcElement* ifcElement = new Ifc4::IfcElement(
		guid::IfcGloballyUniqueId(ifcElementBundle->getModelerElementDescriptor()),
		file.getSingle<Ifc4::IfcOwnerHistory>(),
		ifcElementBundle->getModelerElementDescriptor(),
		ifcElementBundle->getModelerElementDescriptor(),
		boost::none,
		file.addLocalPlacement(),
		elemShape, 
		boost::none);

	return ifcElement;
}

Ifc4::IfcDistributionElement * IfcElementBuilder::buildIfcDistributionElement(IfcElementBundle *& ifcElementBundle, Ifc4::IfcProductDefinitionShape * elemShape, IfcHierarchyHelper<Ifc4>& file)
{
	//Create the pipe as IfcDistributionElement
	Ifc4::IfcDistributionElement* ifcDistributionElem = new Ifc4::IfcDistributionElement(
		guid::IfcGloballyUniqueId(ifcElementBundle->getModelerElementDescriptor()),
		file.getSingle<Ifc4::IfcOwnerHistory>(),
		ifcElementBundle->getModelerElementDescriptor(),
		ifcElementBundle->getModelerElementDescriptor(),
		boost::none,
		file.addLocalPlacement(),
		elemShape,
		boost::none
	);	

	return ifcDistributionElem;
}
