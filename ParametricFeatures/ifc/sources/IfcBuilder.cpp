#include "../headers/IfcBuilder.h"

void IfcBuilder::buildIfcDistributionElem(IfcBundle*& ifcBundle, Ifc4::IfcProductDefinitionShape* elemShape, IfcHierarchyHelper<Ifc4>& file)
{	
	typedef Ifc4::IfcGloballyUniqueId guid;

	//Create the pipe as IfcDistributionElement
	Ifc4::IfcDistributionElement* ifcDistributionElem = new Ifc4::IfcDistributionElement(
		guid::IfcGloballyUniqueId(ifcBundle->getModelerElementName()),
		file.getSingle<Ifc4::IfcOwnerHistory>(), 
		ifcBundle->getModelerElementName(),
		ifcBundle->getModelerElementName(), 
		boost::none, 
		file.addLocalPlacement(), 
		elemShape, 
		boost::none
	);	

	//Set the element to the IfcBundle
	ifcBundle->setIfcElement(ifcDistributionElem);

	//TODO [SB] find a better implementation especially for handling Source and Sink ports
	
	int portSequence = 0;

	IfcTemplatedEntityList<Ifc4::IfcObjectDefinition>* tempEntityList = new IfcTemplatedEntityList<Ifc4::IfcObjectDefinition>();		

	for (Ifc4::IfcPoint* point : ifcBundle->getIfcPortsPointsVector())
	{
		Ifc4::IfcRepresentationItem::list::ptr ifcPortsRepItemList(new Ifc4::IfcRepresentationItem::list());
		Ifc4::IfcRepresentation::list::ptr ifcPortsRepList(new Ifc4::IfcRepresentation::list());

		Ifc4::IfcGeometricRepresentationItem* pointGeom(point);
		ifcPortsRepItemList->push(pointGeom);

		Ifc4::IfcRepresentation* ifcPortsRepresentation = new Ifc4::Ifc4::IfcRepresentation(
			file.getSingle<Ifc4::IfcGeometricRepresentationContext>(),
			std::string("Point Port"),
			std::string("Point Port"),
			ifcPortsRepItemList
		);

		ifcPortsRepList->push(ifcPortsRepresentation);

		Ifc4::IfcProductDefinitionShape* portShape = new Ifc4::IfcProductDefinitionShape(boost::none, boost::none, ifcPortsRepList);

		//TRY TO REMOVE THIS FOR THE REPRESENTATION
		//file.addEntity(portShape);

		//Need to be used the subtype because otherwise the flow , distribution type, distribution system you can specify it
		Ifc4::IfcDistributionPort* port = new Ifc4::IfcDistributionPort(
			std::string("Port test"),
			file.getSingle<Ifc4::IfcOwnerHistory>(),
			ifcBundle->getModelerElementName(),
			ifcBundle->getModelerElementName(),
			std::string("Port test"),
			file.getSingle<Ifc4::IfcObjectPlacement>(),
			portShape,
			Ifc4::IfcFlowDirectionEnum::Value(portSequence),
			Ifc4::IfcDistributionPortTypeEnum::IfcDistributionPortType_PIPE,
			Ifc4::IfcDistributionSystemEnum::IfcDistributionSystem_NOTDEFINED
		);

		//insert the object inside the object definition list list
		tempEntityList->push(port);
		//Add the IfcDistributionPort to the IfcBundleElement
		ifcBundle->addIfcDistributionPorts(port);

		file.addBuildingProduct(port);

		portSequence++;
	}

	//create the shared_ptr with the object definition list
	boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcObjectDefinition>> objectDefinition(tempEntityList);

	//Create the nested relationship between the element and ports
	Ifc4::IfcRelNests * relNests = new Ifc4::IfcRelNests(
		guid::IfcGloballyUniqueId(""),
		file.getSingle<Ifc4::IfcOwnerHistory>(),
		ifcBundle->getModelerElementName(),
		ifcBundle->getModelerElementName(),
		ifcDistributionElem,
		objectDefinition
	);

	file.addEntity(relNests);
	file.addBuildingProduct(ifcDistributionElem);
	
	
}

void IfcBuilder::buildIfcReletionshipConnectionPorts(std::vector<IfcBundle*>ifcRelBundleVector, IfcHierarchyHelper<Ifc4>& file)
{
	for (size_t i = 0; i < ifcRelBundleVector.size()-1; i++)
	{
		IfcBundle* source = ifcRelBundleVector[i];
		IfcBundle* sink = ifcRelBundleVector[i + 1];
		
		/*Ifc4::IfcRelConnectsPorts* connectsPorts = new Ifc4::IfcRelConnectsPorts(
			std::string("Connection"),
			file.getSingle<Ifc4::IfcOwnerHistory>(),
			boost::none,
			boost::none,
			portsVector[0],
			portsVector[1],
			source->addIfcPortsPoints()
		);*/

		Ifc4::IfcDistributionElement* distElem  = dynamic_cast<Ifc4::IfcDistributionElement*>(sink->getIfcElement());

		Ifc4::IfcRelConnectsPortToElement* connectsElement = new Ifc4::IfcRelConnectsPortToElement(
			std::string("Connection Pipes"),
			file.getSingle<Ifc4::IfcOwnerHistory>(),
			boost::none,
			std::string("CONNECTION From: ") + source->getModelerElementName() + std::string("To: ") + sink->getModelerElementName(),
			//boost::none,
			source->getIfcDistributionPortsVector()[1],
			distElem
		);

		file.addEntity(connectsElement);
	}
}

void IfcBuilder::buildIfc(std::vector<DictionaryProperties*>& dictionaryPropertiesVector, std::vector<SmartFeatureContainer*>& smartFeatureContainerVector)
{
		std::string name = "PrimitiveTest";
		IfcHierarchyHelper<Ifc4> file = IfcHierarchyHelper<Ifc4>(IfcParse::schema_by_name("IFC4"));
		std::string filename = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/ifc/" + name + ".ifc";
		//std::string filename = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/ifc/" + name + ".ifc";
		typedef Ifc4::IfcGloballyUniqueId guid2;

		Ifc4::IfcSIUnit* ifcUnitLength = new Ifc4::IfcSIUnit(Ifc4::IfcUnitEnum::IfcUnit_LENGTHUNIT, boost::none, Ifc4::IfcSIUnitName::IfcSIUnitName_METRE);
		Ifc4::IfcSIUnit* ifcUnitAngle = new Ifc4::IfcSIUnit(Ifc4::IfcUnitEnum::IfcUnit_PLANEANGLEUNIT, boost::none, Ifc4::IfcSIUnitName::IfcSIUnitName_RADIAN);

		// TODO [MP] review unit assigment
		IfcEntityList* entityList = new IfcEntityList();
		entityList->push(ifcUnitLength);
		entityList->push(ifcUnitAngle);
		boost::shared_ptr<IfcEntityList> unitEntity(entityList);

		Ifc4::IfcUnitAssignment* unitAssigment = new Ifc4::IfcUnitAssignment(unitEntity);


		Ifc4::IfcProject* project = new Ifc4::IfcProject(guid2::IfcGloballyUniqueId(name), file.getSingle<Ifc4::IfcOwnerHistory>(), boost::none, boost::none,
			boost::none, boost::none, boost::none, boost::none, unitAssigment);

		file.addEntity(project);

		// initialize ifc bundle vector
		std::vector<IfcBundle*>ifcBundleVector;
		if (!dictionaryPropertiesVector.empty())
		{
			for (int i = 0; i < dictionaryPropertiesVector.size(); i++)
			{
				DictionaryProperties& dictionaryProperties = *dictionaryPropertiesVector.at(i);
				IfcBundle* ifcBundle = new IfcBundle(dictionaryProperties.getElementId(),dictionaryProperties.getElementName());
				ifcBundleVector.push_back(ifcBundle);
			}
		}

		// TODO [MP/SB] find another implementation for smart feature
		//if (!smartFeatureContainerVector.empty()) {
		//	for (int i = 0; i < smartFeatureContainerVector.size(); ++i) 
		//	{
		//		SmartFeatureContainer smartFeatureContainer = *smartFeatureContainerVector.at(i);
		//
		//		if (smartFeatureContainer.getRoot() != nullptr)
		//		{
		//			if (smartFeatureContainer.getRoot()->getReaderProperties()->getSmartFeatureGeneralProperties()->getSmartFeatureTypeEnum() == SmartFeatureTypeEnum::BOOLEAN_FEATURE) {
		//				IfcBooleanOperatorHandler* ifcBooleanOperatorHandler = new IfcBooleanOperatorHandler();
		//				representationItem = ifcBooleanOperatorHandler->buildBooleanRepresentation(*smartFeatureContainer.getRoot(), file);
		//			}
		//		}
		//
		//		if (representationItem != nullptr) 
		//		{
		//			items->push(representationItem);
		//		}
		//	}
		//}
		//
		//Ifc4::IfcBuildingElementProxy* ifcBuildingElementProxy = nullptr;
		//
		//// create simple primitives, which are not a smartfeature
		//if (!dictionaryPropertiesVector.empty())
		//{
		//	for (int i = 0; i < dictionaryPropertiesVector.size(); i++)
		//	{
		//		DictionaryProperties& dictionaryProperties = *dictionaryPropertiesVector.at(i);
		//		//if (dictionaryProperties.getGeneralProperties()->getIsSmartFeature()) 
		//		//{
		//		//	continue;
		//		//}
		//		for (auto const& primitivePropertiesValue : dictionaryProperties.getGraphicProperties()->getPrimitiveGraphicPropertiesVector()) 
		//		{
		//			IfcPrimitivesEnhancer* IfcPrimitivesEnhancer = new IfcPrimitivesEnhancer();
		//			ifcBuildingElementProxy = IfcPrimitivesEnhancer->buildIfcPrimitive(*primitivePropertiesValue, dictionaryProperties.getReaderProperties()->getReaderPropertiesBundleVector() ,file);
		//
		//
		//			if (ifcBuildingElementProxy != nullptr) {
		//				/*file.addBuildingProduct(ifcBuildingElementProxy);*/
		//				//Ifc4::IfcRepresentationItem* ceva  = new Ifc4::IfcBooleanResult(Ifc4::IfcBooleanOperator::IfcBooleanOperator_UNION, ifcBuildingElementProxy, pipe);
		//
		//
		//			}
		//		}
		//	}
		//}
		//TODO [MP] create solids builder
//		if (smartFeatureContainer.getRoot() != nullptr)
//		{
//			switch (smartFeatureContainer.getRoot()->getReaderProperties()->getSmartFeatureGeneralProperties()->getSmartFeatureTypeEnum())
//			{
//			case SmartFeatureTypeEnum::BOOLEAN_FEATURE:
//			{
//				IfcBooleanOperatorHandler* ifcBooleanOperatorHandler = new IfcBooleanOperatorHandler();
//				representationItem = ifcBooleanOperatorHandler->buildBooleanRepresentation(*smartFeatureContainer.getRoot(), file);
//			}
//			break;
//			case SmartFeatureTypeEnum::CREATE_SOLIDS:
//			{
//				IfcCreateSolidsOperationBuilder* ifcCreateSolidsOperationBuilder = new IfcCreateSolidsOperationBuilder();
//				representationItem = ifcCreateSolidsOperationBuilder->buildIfcCreateSolidsOperation(*smartFeatureContainer.getRoot(), file);
//			}
//			default:
//				break;
//			}
//
//
//		}
//
//		if (representationItem != nullptr)
//		{
//			items->push(representationItem);
//		}
//}
//		}

		IfcPrimitivesEnhancer* ifcPrimitivesEnhancer = new IfcPrimitivesEnhancer();
		ifcPrimitivesEnhancer->enhanceIfcPrimitives(dictionaryPropertiesVector,ifcBundleVector, file);

		IfcShapesEnhancer* ifcShapesEnhancer = new IfcShapesEnhancer();
		ifcShapesEnhancer->enhanceIfcShapesPrimitives(dictionaryPropertiesVector, ifcBundleVector, file);

		typedef Ifc4::IfcGloballyUniqueId guid;

		//Create the vector for the distribution element 
		std::vector<IfcBundle*>ifcDistributionBundleVector;
		for (auto& ifcBundle : ifcBundleVector) //const& removed
		{
			Ifc4::IfcRepresentationItem::list::ptr ifcRepresentationItemList(new Ifc4::IfcRepresentationItem::list());

			for (auto const& ifcGraphicPropertiesBundle : ifcBundle->getIfcGraphicPropertiesBundleVector()) {

				if (ifcGraphicPropertiesBundle->getIfcRepresentationItem() != nullptr && ifcGraphicPropertiesBundle->getShow()) {
					ifcRepresentationItemList->push(ifcGraphicPropertiesBundle->getIfcRepresentationItem());
				}
			}

			Ifc4::IfcRepresentation* ifcRepresentation = new Ifc4::Ifc4::IfcRepresentation(file.getSingle<Ifc4::IfcGeometricRepresentationContext>(),
				ifcBundle->getModelerElementName(), ifcBundle->getModelerElementName(), ifcRepresentationItemList);

			Ifc4::IfcRepresentation::list::ptr ifcRepresentationList(new Ifc4::IfcRepresentation::list());
			ifcRepresentationList->push(ifcRepresentation);

			Ifc4::IfcProductDefinitionShape* shape = new Ifc4::IfcProductDefinitionShape(boost::none, boost::none, ifcRepresentationList);

			file.addEntity(shape);

			if (ifcBundle->getHasElementConnection())
			{
				ifcDistributionBundleVector.push_back(ifcBundle);
				buildIfcDistributionElem(ifcBundle, shape, file);
			}
			else 
			{
				Ifc4::IfcElement* ifcElement = new Ifc4::IfcElement(guid::IfcGloballyUniqueId(ifcBundle->getModelerElementName()), file.getSingle<Ifc4::IfcOwnerHistory>(), ifcBundle->getModelerElementName(),
					ifcBundle->getModelerElementName(), boost::none, file.addLocalPlacement(), shape, boost::none);

				file.addBuildingProduct(ifcElement);
			}
			
		}

		//if(!ifcDistributionBundleVector.empty())
			//buildIfcReletionshipConnectionPorts(ifcDistributionBundleVector, file);

		IfcPropertiesEnhancer* ifcPropertiesEnhancer = new IfcPropertiesEnhancer();
		ifcPropertiesEnhancer->enhanceIfcProperties(dictionaryPropertiesVector, ifcBundleVector, file);

		IfcMaterialEnhancer* ifcMaterialEnhancer = new IfcMaterialEnhancer();
		ifcMaterialEnhancer->enhanceMaterials(dictionaryPropertiesVector, ifcBundleVector, file);

		std::ofstream f;
		f.open(filename);
		f << file;
		f.close();
}
