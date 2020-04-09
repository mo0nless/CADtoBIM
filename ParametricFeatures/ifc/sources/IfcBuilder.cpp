#include "../headers/IfcBuilder.h"

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
		typedef Ifc4::IfcGloballyUniqueId guid;

		for (auto const& ifcBundle : ifcBundleVector) {
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

			Ifc4::IfcElement* ifcElement = new Ifc4::IfcElement(guid::IfcGloballyUniqueId(ifcBundle->getModelerElementName()), file.getSingle<Ifc4::IfcOwnerHistory>(), ifcBundle->getModelerElementName(),
				ifcBundle->getModelerElementName(), boost::none, file.addLocalPlacement(), shape, boost::none);


			file.addBuildingProduct(ifcElement);
		}

		//TODO [MP/SB] curves builder, find another implementatino

		//	IfcCurvesPrimitivesBuilder* ifcCurvesPrimitivesBuilder = new IfcCurvesPrimitivesBuilder();
		//	std::vector<Ifc4::IfcCurve*> ifcCurvesItemsVector = ifcCurvesPrimitivesBuilder->buildIfcCurvesPrimitives(*dictionaryProperties.getGraphicProperties(), file);
		//
		//	if (!ifcCurvesItemsVector.empty()) {
		//		for each (Ifc4::IfcCurve* curve in ifcCurvesItemsVector)
		//		{
		//			CurvesPrimitivesContainer* curveCotainer;
		//			dictionaryProperties.getGraphicProperties()->tryGetCurvesPrimitivesContainer(curveCotainer);
		//
		//			/*if(curveCotainer->getIsFilled())
		//			{
		//			Ifc4::IfcPlane* plane = new Ifc4::IfcPlane();
		//			representationItem = new Ifc4::IfcCurveBoundedPlane(plane,curve,boost::none);
		//			}
		//			else*/
		//			representationItem = curve;
		//
		//			if (representationItem != nullptr) {
		//				items->push(representationItem);
		//			}
		//		}
		//	}
		//}
		//}
		//
		//Ifc4::IfcShapeRepresentation* rep = new Ifc4::IfcShapeRepresentation(file.getSingle<Ifc4::IfcGeometricRepresentationContext>(), std::string("Body"), std::string("Model"), items);
		//
		//reps->push(rep);
		//file.addEntity(rep);
		//
		//ifcRepresentationList->push(ifc)

		std::ofstream f;
		f.open(filename);
		f << file;
		f.close();
}
