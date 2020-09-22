#include "../headers/IfcElementBuilder.h"

IfcElementBuilder::IfcElementBuilder(Ifc4::IfcGeometricRepresentationContext* geomContext, Ifc4::IfcOwnerHistory* ownerHistory, Ifc4::IfcObjectPlacement* objectPlacement)
{
	this->geometricRepresentationContext = geomContext;
	this->ownerHistory = ownerHistory;
	this->objectPlacement = objectPlacement;

	this->_componentsMappingService = new ComponentsMappingService(Logs::Logger::getLogger());
}

void IfcElementBuilder::processIfcElement(vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file)
{

	vector<ComponentsMappingDTO*> componentsMappings = this->_componentsMappingService->getAll();

	
	//Create the vector for the distribution element 
	//vector<IfcElementBundle*>ifcDistributionBundleVector;
	for (auto& ifcElementBundle : ifcBundleVector) //const& removed
	{
		string rezult = getIfcElement(componentsMappings, ifcElementBundle->getModelerElementDescriptor());
		cout << rezult << endl;

		Ifc4::IfcRepresentationItem::list::ptr ifcRepresentationItemList(new Ifc4::IfcRepresentationItem::list());

		for (auto const& ifcGraphicPropertiesBundle : ifcElementBundle->getIfcGraphicPropertiesBundleVector()) {

			if (ifcGraphicPropertiesBundle->getIfcRepresentationItem() != nullptr && ifcGraphicPropertiesBundle->getShow()) {
				ifcRepresentationItemList->push(ifcGraphicPropertiesBundle->getIfcRepresentationItem());
			}
		}

		string representationType = "";
		string representationIdentifier = "";
		//TODO: Needs to be set up correctly the 3rd input parameter following:
		//https://standards.buildingsmart.org/IFC/DEV/IFC4_2/FINAL/HTML/schema/ifcrepresentationresource/lexical/ifcshaperepresentation.htm
		if (ifcElementBundle->solidModel)
		{
			representationType = "SolidModel";
			representationIdentifier = "Body";
		}
		else
		{
			representationType = "Axis";
			representationIdentifier = "Curve";
		}

		//NOTE  The provision of a model view (IfcGeometricRepresentationContext.ContextType = 'Model') is mandatory. Instances of IfcGeometricRepresentationSubContext relate to it as its ParentContext.
		Ifc4::IfcGeometricRepresentationSubContext* geometricSubContext = new Ifc4::IfcGeometricRepresentationSubContext(
			representationIdentifier,
			geometricRepresentationContext->ContextType(),
			geometricRepresentationContext,
			boost::none,
			Ifc4::IfcGeometricProjectionEnum::IfcGeometricProjection_MODEL_VIEW,
			string("$")
		);

				
		Ifc4::IfcShapeRepresentation* ifcRepresentation = new Ifc4::Ifc4::IfcShapeRepresentation(
			geometricSubContext,
			//file.getSingle<Ifc4::IfcGeometricRepresentationContext>(),
			representationIdentifier,
			representationType,
			ifcRepresentationItemList
		);

		Ifc4::IfcRepresentation::list::ptr ifcRepresentationList(new Ifc4::IfcRepresentation::list());
		ifcRepresentationList->push(ifcRepresentation);

		Ifc4::IfcProductDefinitionShape* shape = new Ifc4::IfcProductDefinitionShape(
			string("$"),
			string("$"),
			ifcRepresentationList
		);

		file.addEntity(shape);
	
		if (rezult == "IfcPipeSegment") {
			Ifc4::IfcPipeSegment* pipeSegment = new Ifc4::IfcPipeSegment(guid::IfcGloballyUniqueId(ifcElementBundle->getModelerElementDescriptor()),
				ownerHistory, ifcElementBundle->getModelerElementDescriptor(), ifcElementBundle->getModelerElementDescriptor(), string("none"), file.addLocalPlacement(), shape,
				string("$"), Ifc4::IfcPipeSegmentTypeEnum::IfcPipeSegmentType_NOTDEFINED);

			file.addBuildingProduct(pipeSegment);
			ifcElementBundle->setIfcElement(pipeSegment);
			continue;
		}


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
		//file.getSingle<Ifc4::IfcOwnerHistory>(),
		ownerHistory,
		ifcElementBundle->getModelerElementDescriptor(),
		ifcElementBundle->getModelerElementDescriptor(),
		//boost::none,
		string("$"),
		file.addLocalPlacement(),
		elemShape, 
		//boost::none
		string("$")
	);

	return ifcElement;
}

Ifc4::IfcDistributionElement * IfcElementBuilder::buildIfcDistributionElement(IfcElementBundle *& ifcElementBundle, Ifc4::IfcProductDefinitionShape * elemShape, IfcHierarchyHelper<Ifc4>& file)
{
	//Create the pipe as IfcDistributionElement
	Ifc4::IfcDistributionElement* ifcDistributionElem = new Ifc4::IfcDistributionElement(
		guid::IfcGloballyUniqueId(ifcElementBundle->getModelerElementDescriptor()),
		//file.getSingle<Ifc4::IfcOwnerHistory>(),
		ownerHistory,
		ifcElementBundle->getModelerElementDescriptor(),
		ifcElementBundle->getModelerElementDescriptor(),
		//boost::none,
		string("$"),
		file.addLocalPlacement(),
		elemShape,
		//boost::none
		string("$")
	);	

	return ifcDistributionElem;
}

string IfcElementBuilder::getIfcElement(vector<ComponentsMappingDTO*> componentsMapping, string elementDescription)
{
	istringstream iss(elementDescription);
	vector<string> elementWords{ istream_iterator<string>{iss}, istream_iterator<string>{} };

	for each (string element in elementWords)
	{
		for each (ComponentsMappingDTO* mapping in componentsMapping)
		{
			if (boost::iequals(element, mapping->getModelerComponentName())) {
				return mapping->getIfcComponentName();
			}
		}
	}
	return string();
}
