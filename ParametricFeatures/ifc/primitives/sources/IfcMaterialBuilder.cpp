void buildMaterial() {
	// TODO [MP] use when needed

	std::string colourName = "myColour";
	Ifc4::IfcColourRgb* ifcColour = new Ifc4::IfcColourRgb(colourName, 252, 98, 3);
	file.addEntity(ifcColour);

	Ifc4::IfcSurfaceStyleRendering* ifcSurfaceStyleRendering = new Ifc4::IfcSurfaceStyleRendering(cacat, 1, new Ifc4::IfcNormalisedRatioMeasure(1), new Ifc4::IfcNormalisedRatioMeasure(1), new Ifc4::IfcNormalisedRatioMeasure(1), new Ifc4::IfcNormalisedRatioMeasure(1), new Ifc4::IfcNormalisedRatioMeasure(1), new Ifc4::IfcNormalisedRatioMeasure(1),Ifc4::IfcReflectanceMethodEnum::IfcReflectanceMethod_BLINN);
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
	file.addEntity(ifcRelAssociatesMaterial);
}

void buildProperty() {
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


	//items->push(ifcRepresentationItem);
}