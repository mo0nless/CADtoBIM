#include "../headers/ParametricFeatures.h"

#ifndef Private
#define Private
#endif


//void buildIfc(std::vector<DictionaryProperties*>& dictionaryPropertiesVector) 
//{
//	boost::none_t const null = boost::none;
//	std::string name = "PrimitiveTest";
//	IfcHierarchyHelper<Ifc4> file = IfcHierarchyHelper<Ifc4>(IfcParse::schema_by_name("IFC4"));
//	//std::string filename = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/ifc/" + name + ".ifc";
//	std::string filename = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/ifc/" + name + ".ifc";
//	typedef Ifc4::IfcGloballyUniqueId guid;
//
//	Ifc4::IfcSIUnit* ifcUnitLength = new Ifc4::IfcSIUnit(Ifc4::IfcUnitEnum::IfcUnit_LENGTHUNIT, boost::none, Ifc4::IfcSIUnitName::IfcSIUnitName_METRE);
//	Ifc4::IfcSIUnit* ifcUnitAngle = new Ifc4::IfcSIUnit(Ifc4::IfcUnitEnum::IfcUnit_PLANEANGLEUNIT, boost::none, Ifc4::IfcSIUnitName::IfcSIUnitName_RADIAN);
//	
//	IfcEntityList* entityList = new IfcEntityList();
//	entityList->push(ifcUnitLength);
//	entityList->push(ifcUnitAngle);
//	boost::shared_ptr<IfcEntityList> unitEntity(entityList);
//
//	Ifc4::IfcUnitAssignment* unitAssigment = new Ifc4::IfcUnitAssignment(unitEntity);
//	Ifc4::IfcProject* project = new Ifc4::IfcProject(guid::IfcGloballyUniqueId(name), file.getSingle<Ifc4::IfcOwnerHistory>(), boost::none, boost::none, boost::none, boost::none, boost::none, boost::none, unitAssigment);
//
//	file.addEntity(project);
//
//	Ifc4::IfcRepresentation::list::ptr reps(new Ifc4::IfcRepresentation::list());
//	Ifc4::IfcRepresentationItem::list::ptr items(new Ifc4::IfcRepresentationItem::list());
//
//	Ifc4::IfcBuildingElementProxy* primitive = new Ifc4::IfcBuildingElementProxy(
//		guid::IfcGloballyUniqueId(name),
//		0,
//		name,
//		boost::none,
//		boost::none,
//		0,
//		0,
//		boost::none,
//		boost::none
//	);
//
//	file.addBuildingProduct(primitive);
//
//	primitive->setOwnerHistory(file.getSingle<Ifc4::IfcOwnerHistory>());
//	primitive->setObjectPlacement(file.addLocalPlacement());
//
//	int micrometer = 1000000;
//
//	for (int i = 0; i < dictionaryPropertiesVector.size(); ++i) {
//		DictionaryProperties& dictionaryProperties = *dictionaryPropertiesVector.at(i);
//
//		if (dictionaryProperties.getGeneralProperties()->getIsSmartFeature()) {
//			continue;
//		}
//		
//		/*Ifc4::IfcAxis2Placement3D* place = buildIfcAxis2Placement3D(dictionaryProperties, file);
//
//		Ifc4::IfcRepresentationItem* item = nullptr;
//		if (dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::SPHERE || dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::BOX||
//			dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::CONE || dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::CYLINDER) 
//		{
//			item = buildPrimitive(dictionaryProperties, place, file);
//		}
//		else if (dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::TORUS) 
//		{
//			item = buildComplexPrimitive(dictionaryProperties, place, file);
//		}
//
//		if (item == nullptr) {
//			continue;
//		}*/
//
//		CurvesPrimitivesContainer* curveContainer;
//		dictionaryProperties.getGraphicProperties()->tryGetCurvesPrimitivesContainer(curveContainer);
//		
//		for each (BsplineGraphicProperties* curveProperties in curveContainer->getCurvesPrimitivesContainerVector())
//		{
//			IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>* temp = new IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>();
//
//			for (size_t k = 0; k < curveProperties->getControlPoints().size(); k++)
//			{
//				std::vector<double> p;
//				p.push_back(curveProperties->getControlPoints().at(k).x / micrometer);
//				p.push_back(curveProperties->getControlPoints().at(k).y / micrometer);
//				p.push_back(curveProperties->getControlPoints().at(k).z / micrometer);
//
//				Ifc4::IfcCartesianPoint* cP = new Ifc4::IfcCartesianPoint(p);
//				temp->push(cP);
//			}
//
//			file.addEntities(temp->generalize());
//
//			// TODO [MP[ check this shit out
//			// set primitive graphic dictionary if it's a primitive
//			//PrimitiveTypeEnum::PrimitiveTypeEnum primitiveTypeEnum = PrimitiveTypeEnumUtils::getPrimitiveTypeEnumByElementDescription(StringUtils::getString(elDescr.GetWCharCP()));
//			//if (primitiveTypeEnum != PrimitiveTypeEnum::PrimitiveTypeEnum::NONE) {
//			//	PrimitiveGraphicProperties* primitiveGraphicProperties = new PrimitiveGraphicProperties();
//			//	primitiveGraphicProperties->setPrimitiveTypeEnum(primitiveTypeEnum);
//			//	propertiesDictionary->getGraphicProperties()->setPrimitiveGraphicProperties(primitiveGraphicProperties);
//			//}
//
//			boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCartesianPoint>> controlP(temp);
//
//
//			Ifc4::IfcRepresentationItem* item = new Ifc4::IfcBSplineCurve(
//				curveProperties->getDegree(),
//				controlP,
//				Ifc4::IfcBSplineCurveForm::IfcBSplineCurveForm_UNSPECIFIED,
//				curveProperties->getIsCLosed(),
//				curveProperties->getIsSelfIntersect()
//			);
//
//
//			file.addEntity(item);
//			items->push(item);
//		}
//
//		Ifc4::IfcShapeRepresentation* rep = new Ifc4::IfcShapeRepresentation(
//			file.getSingle<Ifc4::IfcGeometricRepresentationContext>(), std::string("Body") + std::to_string(i), std::string("Model") + std::to_string(i), items);
//
//		reps->push(rep);
//
//		file.addEntity(rep);
//	}
//	
//
//	Ifc4::IfcProductDefinitionShape* shape = new Ifc4::IfcProductDefinitionShape(boost::none, boost::none, reps);
//
//	file.addEntity(shape);
//
//	primitive->setRepresentation(shape);
//
//	std::ofstream f;
//	f.open(filename);
//	f << file;
//	f.close();
//}


#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4189)
StatusInt GetSmartFeatureTree(WCharCP unparsedP)
{
	InitializationEnhancer* initializationEnhancer = new InitializationEnhancer();
	
	std::vector<DictionaryProperties*> propsDictVec;
	std::vector<SmartFeatureContainer*> smartFeatureContainerVector;

	initializationEnhancer->processDgnGraphicsElements(propsDictVec, smartFeatureContainerVector);
	
	propsDictVec = initializationEnhancer->orderDictionaryPropertyAndSmartFeature(propsDictVec, smartFeatureContainerVector);

	IfcBuilder* ifcBuilder = new IfcBuilder();
	ifcBuilder->buildIfc(propsDictVec, smartFeatureContainerVector);

	//outfile.close();

	return SUCCESS;
}
#pragma warning( pop ) 


/*=================================================================================**//**
* @description  Unload this application
* @param[in] unparsed Additional input supplied after command string.
+===============+===============+===============+===============+===============+======*/
void UnloadParametricFeatures(WCharCP unparsedP)
{
	auto taskID = mdlSystem_getCurrTaskID();
	mdlDialog_cmdNumberQueue(FALSE, CMD_MDL_UNLOAD, taskID, INPUTQ_HEAD); //INPUTQ_EOQ
	return;
}
