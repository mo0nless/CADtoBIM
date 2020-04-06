#include "../headers/IfcBuilder.h"

void IfcBuilder::buildIfc(std::vector<DictionaryProperties*>& dictionaryPropertiesVector, std::vector<SmartFeatureContainer*> & smartFeatureContainerVector)
{
		std::string name = "PrimitiveTest";
		IfcHierarchyHelper<Ifc4> file = IfcHierarchyHelper<Ifc4>(IfcParse::schema_by_name("IFC4"));
		//std::string filename = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/ifc/" + name + ".ifc";
		std::string filename = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/ifc/" + name + ".ifc";
		typedef Ifc4::IfcGloballyUniqueId guid2;

		Ifc4::IfcSIUnit* ifcUnitLength = new Ifc4::IfcSIUnit(Ifc4::IfcUnitEnum::IfcUnit_LENGTHUNIT, boost::none, Ifc4::IfcSIUnitName::IfcSIUnitName_METRE);
		Ifc4::IfcSIUnit* ifcUnitAngle = new Ifc4::IfcSIUnit(Ifc4::IfcUnitEnum::IfcUnit_PLANEANGLEUNIT, boost::none, Ifc4::IfcSIUnitName::IfcSIUnitName_RADIAN);

		IfcEntityList* entityList = new IfcEntityList();
		entityList->push(ifcUnitLength);
		entityList->push(ifcUnitAngle);
		boost::shared_ptr<IfcEntityList> unitEntity(entityList);

		Ifc4::IfcUnitAssignment* unitAssigment = new Ifc4::IfcUnitAssignment(unitEntity);

		Ifc4::IfcProject* project = new Ifc4::IfcProject(guid2::IfcGloballyUniqueId(name), file.getSingle<Ifc4::IfcOwnerHistory>(), boost::none, boost::none,
			boost::none, boost::none, boost::none, boost::none, unitAssigment);

		file.addEntity(project);

		// TODO [MP/SB] find another implementation for smart feature
		//if (!smartFeatureContainerVector.empty()) {
		//	for (int i = 0; i < smartFeatureContainerVector.size(); ++i) 
		//	{
		//		SmartFeatureContainer smartFeatureContainer = *smartFeatureContainerVector.at(i);

		//		if (smartFeatureContainer.getRoot() != nullptr)
		//		{
		//			if (smartFeatureContainer.getRoot()->getReaderProperties()->getSmartFeatureGeneralProperties()->getSmartFeatureTypeEnum() == SmartFeatureTypeEnum::BOOLEAN_FEATURE) {
		//				IfcBooleanOperatorHandler* ifcBooleanOperatorHandler = new IfcBooleanOperatorHandler();
		//				representationItem = ifcBooleanOperatorHandler->buildBooleanRepresentation(*smartFeatureContainer.getRoot(), file);
		//			}
		//		}

		//		if (representationItem != nullptr) 
		//		{
		//			items->push(representationItem);
		//		}
		//	}
		//}

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
		//			IfcPrimitivesBuilder* ifcPrimitivesBuilder = new IfcPrimitivesBuilder();
		//			ifcBuildingElementProxy = ifcPrimitivesBuilder->buildIfcPrimitive(*primitivePropertiesValue, dictionaryProperties.getReaderProperties()->getReaderPropertyBundleVector() ,file);


		//			if (ifcBuildingElementProxy != nullptr) {
		//				/*file.addBuildingProduct(ifcBuildingElementProxy);*/
		//				//Ifc4::IfcRepresentationItem* ceva  = new Ifc4::IfcBooleanResult(Ifc4::IfcBooleanOperator::IfcBooleanOperator_UNION, ifcBuildingElementProxy, pipe);


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

		IfcPrimitivesBuilder* ifcPrimitivesBuilder = new IfcPrimitivesBuilder();
		std::vector<Ifc4::IfcRepresentation*>ifcRepresentationVector = ifcPrimitivesBuilder->buildIfcPrimitives(dictionaryPropertiesVector,file);

		//Ifc4::IfcRepresentation* ifcRepresentation = new Ifc4::IfcRepresentation(
		for (auto const& ifcRepresentationItem : ifcRepresentationVector)
		{
			typedef Ifc4::IfcGloballyUniqueId guid;
			Ifc4::IfcProduct* ifcBuildingElementProxy = new Ifc4::IfcProduct(guid::IfcGloballyUniqueId(name), file.getSingle<Ifc4::IfcOwnerHistory>(),name,
				boost::none,boost::none, file.addLocalPlacement(),0);
			//ifcBuildingElementProxy->setOwnerHistory(file.getSingle<Ifc4::IfcOwnerHistory>());
			//ifcBuildingElementProxy->setObjectPlacement(file.addLocalPlacement());

			Ifc4::IfcRepresentation::list::ptr reps(new Ifc4::IfcRepresentation::list());
			/*Ifc4::IfcRepresentationItem::list::ptr items(new Ifc4::IfcRepresentationItem::list());*/


			if (ifcRepresentationItem != nullptr) 
			{

				
				//std::string propertyName = "IfcColourRgb";
				//std::string propertyDesc = "colourName, 0.8, 0.7, 0.1";
				//Ifc4::IfcProperty* ifcProperty = new Ifc4::IfcProperty(propertyName, propertyDesc);
				//file.addEntity(ifcProperty);


				//IfcTemplatedEntityList<Ifc4::IfcProperty>* templatedList1 = new IfcTemplatedEntityList<Ifc4::IfcProperty>();
				//templatedList1->push(ifcProperty);
				//boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcProperty>> propertySetList(templatedList1);

				//std::string propertySetName = "propertySetName";
				//Ifc4::IfcPropertySet* ifcPropertySet = new Ifc4::IfcPropertySet(guid::IfcGloballyUniqueId(name), file.getSingle<Ifc4::IfcOwnerHistory>(), propertySetName, boost::none, propertySetList);
				//file.addEntity(ifcPropertySet);

				//std::string refDefinesName = "refDefinesName";
				//IfcTemplatedEntityList<Ifc4::IfcObjectDefinition>* templatedList2 = new IfcTemplatedEntityList<Ifc4::IfcObjectDefinition>();
				//templatedList2->push(ifcBuildingElementProxy);
				//boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcObjectDefinition>> objectDefinitionList(templatedList2);

				////new Ifc4::IfcRelDefinesByProperties()
				//Ifc4::IfcRelDefinesByProperties* ifcRelDefinesByProperties = new Ifc4::IfcRelDefinesByProperties(guid::IfcGloballyUniqueId(name), file.getSingle<Ifc4::IfcOwnerHistory>(), refDefinesName,
				//	boost::none, objectDefinitionList, ifcPropertySet);
				//file.addEntity(ifcRelDefinesByProperties);

				//Ifc4::IfcProductRepresentation* IfcProductRepresentation = new Ifc4::IfcProductRepresentation()

				// TODO [MP] find more abstract implementation usingg IfcProperty and IfcPropertySet
				/*std::string culoare = "RED";
				Ifc4::IfcColourSpecification* cacat = new Ifc4::IfcColourSpecification(culoare);*/
				//Ifc4::IfcPreDefinedColour* ceva = new Ifc4::IfcPreDefinedColour("RED");
				
				/*file.addEntity(cacat);
				std::string colourName = "myColour";*/
				/*Ifc4::IfcColourRgb* ifcColour = new Ifc4::IfcColourRgb(colourName, 252, 98, 3);
				file.addEntity(ifcColour);*/

				/*Ifc4::IfcSurfaceStyleRendering* ifcSurfaceStyleRendering = new Ifc4::IfcSurfaceStyleRendering(cacat, 1, new Ifc4::IfcNormalisedRatioMeasure(1), new Ifc4::IfcNormalisedRatioMeasure(1), new Ifc4::IfcNormalisedRatioMeasure(1), new Ifc4::IfcNormalisedRatioMeasure(1), new Ifc4::IfcNormalisedRatioMeasure(1), new Ifc4::IfcNormalisedRatioMeasure(1),Ifc4::IfcReflectanceMethodEnum::IfcReflectanceMethod_BLINN);
				file.addEntity(ifcSurfaceStyleRendering);

				IfcEntityList* entityList3 = new IfcEntityList();
				entityList3->push(ifcSurfaceStyleRendering);
				boost::shared_ptr<IfcEntityList> unitEntity3(entityList3);
				Ifc4::IfcSurfaceStyle* ifcSurfaceStyle = new Ifc4::IfcSurfaceStyle(colourName, Ifc4::IfcSurfaceSide::IfcSurfaceSide_BOTH, unitEntity3);
				file.addEntity(ifcSurfaceStyle);

				IfcEntityList* entityList4 = new IfcEntityList();
				entityList4->push(ifcSurfaceStyle);
				boost::shared_ptr<IfcEntityList> unitEntity4(entityList4);
				Ifc4::IfcPresentationStyleAssignment* ifcPresentationStyleAssignment = new Ifc4::IfcPresentationStyleAssignment(unitEntity4);
				file.addEntity(ifcPresentationStyleAssignment);

				IfcEntityList* entityList5 = new IfcEntityList();
				entityList5->push(ifcPresentationStyleAssignment);
				boost::shared_ptr<IfcEntityList> unitEntity5(entityList5);
				Ifc4::IfcStyledItem* ifcStyledItem = new Ifc4::IfcStyledItem(ifcRepresentationItem, unitEntity5, boost::none);
				file.addEntity(ifcStyledItem);


				IfcTemplatedEntityList<Ifc4::IfcRepresentationItem>* ceva2 = new IfcTemplatedEntityList<Ifc4::IfcRepresentationItem>();
				ceva2->push(ifcStyledItem);
				boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcRepresentationItem>> unitEntity6(ceva2);
				Ifc4::IfcStyledRepresentation* ifcStyledRepresentation = new Ifc4::IfcStyledRepresentation(file.getSingle<Ifc4::IfcGeometricRepresentationContext>(), boost::none,
					boost::none, unitEntity6);
				file.addEntity(ifcStyledRepresentation);


				IfcTemplatedEntityList<Ifc4::IfcRepresentation>* ceva1 = new IfcTemplatedEntityList<Ifc4::IfcRepresentation>();
				ceva1->push(ifcStyledRepresentation);
				boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcRepresentation>> unitEntity7(ceva1);
				Ifc4::IfcMaterial* IfcMaterial = new Ifc4::IfcMaterial("Material", boost::none, boost::none);

				Ifc4::IfcMaterialDefinitionRepresentation* ifcMaterialDefinitionRepresentation = new Ifc4::IfcMaterialDefinitionRepresentation(boost::none,boost::none,
					unitEntity7, IfcMaterial);
				file.addEntity(ifcMaterialDefinitionRepresentation);

				IfcEntityList* entityList8 = new IfcEntityList();
				entityList8->push(ifcBuildingElementProxy);
				boost::shared_ptr<IfcEntityList> unitEntity8(entityList8);
				Ifc4::IfcRelAssociatesMaterial* ifcRelAssociatesMaterial = new Ifc4::IfcRelAssociatesMaterial(guid::IfcGloballyUniqueId(name), file.getSingle<Ifc4::IfcOwnerHistory>(),
					boost::none,boost::none, unitEntity8, IfcMaterial);
				file.addEntity(ifcRelAssociatesMaterial);*/

				//items->push(ifcRepresentationItem);

				reps->push(ifcRepresentationItem);
				file.addEntity(ifcRepresentationItem);
			}

		//TODO [MP/SB] curves builder, find another implementatino

		//	IfcCurvesPrimitivesBuilder* ifcCurvesPrimitivesBuilder = new IfcCurvesPrimitivesBuilder();
		//	std::vector<Ifc4::IfcCurve*> ifcCurvesItemsVector = ifcCurvesPrimitivesBuilder->buildIfcCurvesPrimitives(*dictionaryProperties.getGraphicProperties(), file);

		//	if (!ifcCurvesItemsVector.empty()) {
		//		for each (Ifc4::IfcCurve* curve in ifcCurvesItemsVector)
		//		{
		//			CurvesPrimitivesContainer* curveCotainer;
		//			dictionaryProperties.getGraphicProperties()->tryGetCurvesPrimitivesContainer(curveCotainer);

		//			/*if(curveCotainer->getIsFilled())
		//			{
		//			Ifc4::IfcPlane* plane = new Ifc4::IfcPlane();
		//			representationItem = new Ifc4::IfcCurveBoundedPlane(plane,curve,boost::none);
		//			}
		//			else*/
		//			representationItem = curve;

		//			if (representationItem != nullptr) {
		//				items->push(representationItem);
		//			}
		//		}
		//	}
		//}
		//}

			//Ifc4::IfcShapeRepresentation* rep = new Ifc4::IfcShapeRepresentation(file.getSingle<Ifc4::IfcGeometricRepresentationContext>(), std::string("Body"), std::string("Model"), items);

			//reps->push(rep);
			//file.addEntity(rep);

			Ifc4::IfcProductDefinitionShape* shape = new Ifc4::IfcProductDefinitionShape(boost::none, boost::none, reps);

			file.addEntity(shape);

			ifcBuildingElementProxy->setRepresentation(shape);

			file.addBuildingProduct(ifcBuildingElementProxy);
		}
		std::ofstream f;
		f.open(filename);
		f << file;
		f.close();
}
