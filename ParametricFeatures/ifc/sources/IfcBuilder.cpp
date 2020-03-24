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


		Ifc4::IfcRepresentation::list::ptr reps(new Ifc4::IfcRepresentation::list());
		Ifc4::IfcRepresentationItem::list::ptr items(new Ifc4::IfcRepresentationItem::list());

		Ifc4::IfcBuildingElementProxy* primitive = new Ifc4::IfcBuildingElementProxy(
			guid2::IfcGloballyUniqueId(name),
			0,
			name,
			boost::none,
			boost::none,
			0,
			0,
			boost::none,
			boost::none
		);

		file.addBuildingProduct(primitive);

		primitive->setOwnerHistory(file.getSingle<Ifc4::IfcOwnerHistory>());
		primitive->setObjectPlacement(file.addLocalPlacement());


		Ifc4::IfcRepresentationItem* representationItem = nullptr;

		if (!smartFeatureContainerVector.empty()) {
			for (int i = 0; i < smartFeatureContainerVector.size(); ++i) 
			{
				SmartFeatureContainer smartFeatureContainer = *smartFeatureContainerVector.at(i);

				if (smartFeatureContainer.getRoot() != nullptr)
				{
					if (smartFeatureContainer.getRoot()->getReaderProperties()->getSmartFeatureGeneralProperties()->getSmartFeatureTypeEnum() == SmartFeatureTypeEnum::SmartFeatureTypeEnum::BOOLEAN_FEATURE) {
						IfcBooleanOperatorHandler* ifcBooleanOperatorHandler = new IfcBooleanOperatorHandler();
						representationItem = ifcBooleanOperatorHandler->buildBooleanRepresentation(*smartFeatureContainer.getRoot(), file);
					}
				}

				if (representationItem != nullptr) 
				{
					items->push(representationItem);
				}
			}
		}

		
		// create simple primitives, which are not a smartfeature
		if (!dictionaryPropertiesVector.empty())
		{
			for (int i = 0; i < dictionaryPropertiesVector.size(); i++)
			{
				DictionaryProperties& dictionaryProperties = *dictionaryPropertiesVector.at(i);
				if (dictionaryProperties.getGeneralProperties()->getIsSmartFeature()) {
					continue;
				}

				IfcPrimitivesBuilder* ifcPrimitivesBuilder = new IfcPrimitivesBuilder();
				representationItem = ifcPrimitivesBuilder->buildIfcPrimitive(*dictionaryProperties.getGraphicProperties(), file);


				if (representationItem != nullptr) {
					items->push(representationItem);
				}


			}
		}

		Ifc4::IfcShapeRepresentation* rep = new Ifc4::IfcShapeRepresentation(
			file.getSingle<Ifc4::IfcGeometricRepresentationContext>(), std::string("Body"), std::string("Model"), items);

		reps->push(rep);
		file.addEntity(rep);

		Ifc4::IfcProductDefinitionShape* shape = new Ifc4::IfcProductDefinitionShape(boost::none, boost::none, reps);

		file.addEntity(shape);

		primitive->setRepresentation(shape);

		std::ofstream f;
		f.open(filename);
		f << file;
		f.close();
}
