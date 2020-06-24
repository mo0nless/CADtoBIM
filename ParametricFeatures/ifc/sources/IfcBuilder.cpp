#include "../headers/IfcBuilder.h"


void IfcBuilder::buildIfc(std::vector<DictionaryProperties*>& dictionaryPropertiesVector, std::vector<SmartFeatureContainer*>& smartFeatureContainerVector)
{	
	std::string name = "Test-" + dictionaryPropertiesVector[0]->getElementDescriptor();
	IfcHierarchyHelper<Ifc4> file = IfcHierarchyHelper<Ifc4>(IfcParse::schema_by_name("IFC4"));
	std::string filename = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/ifc/" + name + ".ifc";
	//std::string filename = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/ifc/" + name + ".ifc";
	typedef Ifc4::IfcGloballyUniqueId guid;

	Ifc4::IfcSIUnit* ifcUnitLength = new Ifc4::IfcSIUnit(Ifc4::IfcUnitEnum::IfcUnit_LENGTHUNIT, boost::none, Ifc4::IfcSIUnitName::IfcSIUnitName_METRE);
	Ifc4::IfcSIUnit* ifcUnitAngle = new Ifc4::IfcSIUnit(Ifc4::IfcUnitEnum::IfcUnit_PLANEANGLEUNIT, boost::none, Ifc4::IfcSIUnitName::IfcSIUnitName_RADIAN);

	// TODO [MP] review unit assigment
	IfcEntityList* entityList = new IfcEntityList();
	entityList->push(ifcUnitLength);
	entityList->push(ifcUnitAngle);
	boost::shared_ptr<IfcEntityList> unitEntity(entityList);

	Ifc4::IfcUnitAssignment* unitAssigment = new Ifc4::IfcUnitAssignment(unitEntity);

	//NOTE The inherited attribute ContextType shall have one of the following recognized values: 'Sketch', 'Outline', 'Design', 'Detail', 'Model', 'Plan', 'NotDefined'.
	std::string representationIdentifier = "*";
	std::string representationContextType = "Model"; //This is related to the specification of the context
	
	Ifc4::IfcDirection* trueNorthDirection = new Ifc4::IfcDirection(std::vector<double>{ 0.0, 1.0}); //This describe a plane and is 2D

	Ifc4::IfcAxis2Placement3D* originAndAxisPlacement = new Ifc4::IfcAxis2Placement3D(
		file.addTriplet<Ifc4::IfcCartesianPoint>(0, 0, 0),
		file.addTriplet<Ifc4::IfcDirection>(0, 0, 1), // Z direction
		file.addTriplet<Ifc4::IfcDirection>(1, 0, 0) 
	);

	//http://standards.buildingsmart.org/MVD/RELEASE/IFC4/ADD2_TC1/RV1_2/HTML/schema/ifcrepresentationresource/lexical/ifcgeometricrepresentationcontext.htm
	Ifc4::IfcGeometricRepresentationContext* geometricContext = new Ifc4::IfcGeometricRepresentationContext(
		representationIdentifier,
		representationContextType,
		3,
		1.0E-05,
		//file.addTriplet<Ifc4::IfcAxis2Placement3D>(4,4,4),
		originAndAxisPlacement,
		trueNorthDirection
	);

	IfcTemplatedEntityList<Ifc4::IfcRepresentationContext>* listContext = new IfcTemplatedEntityList<Ifc4::IfcRepresentationContext>();
	listContext->push(geometricContext);
	boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcRepresentationContext>> representationContextList(listContext);
	
	//TODO[SB] Set up owner History
	//Ifc4::IfcOwnerHistory()

	Ifc4::IfcProject* project = new Ifc4::IfcProject(
		guid::IfcGloballyUniqueId(name), 
		file.getSingle<Ifc4::IfcOwnerHistory>(), 
		std::string("OpenPlant IFC Exporter"), 
		boost::none,
		boost::none, 
		boost::none, 
		boost::none, 
		representationContextList,
		unitAssigment
	);

	file.addEntity(project);

	// initialize ifc bundle vector
	std::vector<IfcElementBundle*>ifcElementBundleVector;
	if (!dictionaryPropertiesVector.empty())
	{
		for (int i = 0; i < dictionaryPropertiesVector.size(); i++)
		{
			DictionaryProperties& dictionaryProperties = *dictionaryPropertiesVector.at(i);

			IfcElementBundle* ifcElementBundle = new IfcElementBundle(dictionaryProperties.getElementId(), dictionaryProperties.getElementDescriptor());

			ifcElementBundle->setIsSmartSolid(dictionaryProperties.getIsSmartSolid());

			if (dictionaryProperties.getIsSmartSolid() || dictionaryProperties.getIsPrimitiveSolid())
				ifcElementBundle->solidModel = true;

			ifcElementBundle->setSmartFeatureContainer(dictionaryProperties.getSmartFeatureContainer());
			// TODO [MP] to be replaced with a copy contructor or delete dicionary properties and only keep ifc element bundle
			for (auto const& readerProperty : dictionaryProperties.getReaderPropertiesBundleVector()) {
				ReaderPropertiesBundle* readerPropertiesBundle = new ReaderPropertiesBundle(readerProperty->getCassName(), readerProperty->getLocalId());
				for (auto const& property1 : readerProperty->getProperties()) {
					ReaderPropertyDefinition* readerPropertyDefinition = new ReaderPropertyDefinition(property1->getPropertyName(), property1->getPropertyTypeName()
						, property1->getPropertyValue(), property1->getPropertyValueAsString());
					readerPropertiesBundle->addProperty(readerPropertyDefinition);

				}
				ifcElementBundle->addIfcReaderPropertiesBundle(new IfcReaderPropertiesBundle(readerPropertiesBundle));
			}
			ifcElementBundleVector.push_back(ifcElementBundle);
		}
	}

	IfcPrimitivesEnhancer* ifcPrimitivesEnhancer = new IfcPrimitivesEnhancer();
	ifcPrimitivesEnhancer->enhanceIfcPrimitives(dictionaryPropertiesVector,ifcElementBundleVector, file);

	IfcShapesEnhancer* ifcShapesEnhancer = new IfcShapesEnhancer();
	ifcShapesEnhancer->enhanceIfcShapesPrimitives(dictionaryPropertiesVector, ifcElementBundleVector, file);

	SmartFeatureHandler* smartFeatureHandler = new SmartFeatureHandler();
	smartFeatureHandler->handleSmartFeature(ifcElementBundleVector,file);

	IfcBRepSolidsEnhancer* ifcBRepSolidsEnhancer = new IfcBRepSolidsEnhancer();
	ifcBRepSolidsEnhancer->enhanceIfcBRepSolidsEnhancer(dictionaryPropertiesVector, ifcElementBundleVector, file);
	


	IfcElementBuilder* ifcElementBuilder = new IfcElementBuilder();
	ifcElementBuilder->processIfcElement(ifcElementBundleVector, file);
		
	IfcPropertiesEnhancer* ifcPropertiesEnhancer = new IfcPropertiesEnhancer();
	ifcPropertiesEnhancer->enhanceIfcProperties(dictionaryPropertiesVector, ifcElementBundleVector, file);

	//DGN mmmens01 CRASH HERE
	//IfcMaterialEnhancer* ifcMaterialEnhancer = new IfcMaterialEnhancer();
	//ifcMaterialEnhancer->enhanceMaterials(dictionaryPropertiesVector, ifcElementBundleVector, file);

	IfcPortsBuilder* ifcPortsBuilder = new IfcPortsBuilder(geometricContext);
	ifcPortsBuilder->processIfcPorts(ifcElementBundleVector, file);
				
	std::ofstream f;
	f.open(filename);
	f << file;
	f.close();

}
