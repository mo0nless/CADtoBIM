#include "../headers/IfcMaterialEnhancer.h"

void IfcMaterialEnhancer::enhanceMaterials(std::vector<DictionaryProperties*>& dictionaryPropertiesVector, std::vector<IfcBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file)
{

	if (!dictionaryPropertiesVector.empty())
	{
		for (int i = 0; i < dictionaryPropertiesVector.size(); i++)
		{
			DictionaryProperties& dictionaryProperties = *dictionaryPropertiesVector.at(i);

			// TODO [MP] to be replaced with method to check by id. order doesnt guarantee that it's the correct element
			IfcBundle*& ifcBundle = ifcBundleVector.at(i);

			Ifc4::IfcObjectDefinition::list::ptr ifcObjectDefinitionList(new Ifc4::IfcObjectDefinition::list());
			ifcObjectDefinitionList->push(ifcBundle->getIfcElement());
			//IfcTemplatedEntityList<Ifc4::IfcElement>* templatedList2 = new IfcTemplatedEntityList<Ifc4::IfcElement>();

			for (auto const& readerPropertyBundle : dictionaryProperties.getReaderPropertiesBundleVector()) {
				processMaterials(*readerPropertyBundle,file, *ifcBundle);
			}
		}
	}
}

void IfcMaterialEnhancer::processMaterials(ReaderPropertiesBundle& readerPropertiesBundle, IfcHierarchyHelper<Ifc4>& file, IfcBundle& ifcBundle)
{
	for (auto const& readerPropertyDefinition : readerPropertiesBundle.getProperties()) {
		if (readerPropertyDefinition->getPropertyName().find("Color") != std::string::npos) {
			processColour(*readerPropertyDefinition,file, ifcBundle);
		} else 	if (readerPropertyDefinition->getPropertyName().find("Material") != std::string::npos) {
			processMaterial(*readerPropertyDefinition,file, ifcBundle.getIfcElement());
		}
	}
}

void IfcMaterialEnhancer::processColour(ReaderPropertyDefinition& readerPropertyDefinition, IfcHierarchyHelper<Ifc4>& file, IfcBundle& ifcBundle)
{
	typedef Ifc4::IfcGloballyUniqueId guid;

	Ifc4::IfcColourRgb* ifcColour = parseAndCreateColour(readerPropertyDefinition.getPropertyValueAsString());

	Ifc4::IfcSurfaceStyleRendering* ifcSurfaceStyleRendering = new Ifc4::IfcSurfaceStyleRendering(ifcColour, 1, new Ifc4::IfcNormalisedRatioMeasure(1),
		new Ifc4::IfcNormalisedRatioMeasure(1), new Ifc4::IfcNormalisedRatioMeasure(1), new Ifc4::IfcNormalisedRatioMeasure(1), new Ifc4::IfcNormalisedRatioMeasure(1),
		new Ifc4::IfcNormalisedRatioMeasure(1), Ifc4::IfcReflectanceMethodEnum::IfcReflectanceMethod_BLINN);
	file.addEntity(ifcSurfaceStyleRendering);

	IfcEntityList* entityList3 = new IfcEntityList();
	entityList3->push(ifcSurfaceStyleRendering);
	boost::shared_ptr<IfcEntityList> unitEntity3(entityList3);

	Ifc4::IfcSurfaceStyle* ifcSurfaceStyle = new Ifc4::IfcSurfaceStyle(std::string("ColourSurfaceStyle"), Ifc4::IfcSurfaceSide::IfcSurfaceSide_BOTH, unitEntity3);
	file.addEntity(ifcSurfaceStyle);


	IfcEntityList* ifcSurfaceStyleList = new IfcEntityList();
	ifcSurfaceStyleList->push(ifcSurfaceStyle);
	boost::shared_ptr<IfcEntityList> ifcSurfaceStyleSharedList(ifcSurfaceStyleList);
	Ifc4::IfcPresentationStyleAssignment* ifcPresentationStyleAssignment = new Ifc4::IfcPresentationStyleAssignment(ifcSurfaceStyleSharedList);
	file.addEntity(ifcPresentationStyleAssignment);

	IfcEntityList* entityIfcPresentationStyleAssignmentList = new IfcEntityList();
	entityIfcPresentationStyleAssignmentList->push(ifcPresentationStyleAssignment);
	boost::shared_ptr<IfcEntityList> IfcPresentationStyleAssignmentList(entityIfcPresentationStyleAssignmentList);
	Ifc4::IfcRepresentationItem::list::ptr styledItemList(new Ifc4::IfcRepresentationItem::list());

	for (int i = 0; i < ifcBundle.getIfcGraphicPropertiesBundleVector().size(); ++i) {
		Ifc4::IfcStyledItem* ifcStyledItem = new Ifc4::IfcStyledItem(ifcBundle.getIfcGraphicPropertiesBundleVector().at(i)->getIfcRepresentationItem(), IfcPresentationStyleAssignmentList, boost::none);
		file.addEntity(ifcStyledItem);
		styledItemList->push(ifcStyledItem);
	}

	Ifc4::IfcStyledItem* ifcStyledItem = new Ifc4::IfcStyledItem(ifcBundle.getIfcGraphicPropertiesBundleVector().at(0)->getIfcRepresentationItem(), IfcPresentationStyleAssignmentList, boost::none);
	file.addEntity(ifcStyledItem);
	styledItemList->push(ifcStyledItem);
	Ifc4::IfcStyledRepresentation* ifcStyledRepresentation = new Ifc4::IfcStyledRepresentation(file.getSingle<Ifc4::IfcRepresentationContext>(), boost::none,
		boost::none, styledItemList);
	file.addEntity(ifcStyledRepresentation);


	IfcTemplatedEntityList<Ifc4::IfcRepresentation>* ceva1 = new IfcTemplatedEntityList<Ifc4::IfcRepresentation>();
	ceva1->push(ifcStyledRepresentation);
	boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcRepresentation>> unitEntity7(ceva1);
	Ifc4::IfcMaterial* ifcMaterial = new Ifc4::IfcMaterial("Material", boost::none, boost::none);

	Ifc4::IfcMaterialDefinitionRepresentation* ifcMaterialDefinitionRepresentation = new Ifc4::IfcMaterialDefinitionRepresentation(boost::none, boost::none,
		unitEntity7, ifcMaterial);
	file.addEntity(ifcMaterialDefinitionRepresentation);

	IfcEntityList* entityList8 = new IfcEntityList();
	entityList8->push(ifcBundle.getIfcElement());
	boost::shared_ptr<IfcEntityList> unitEntity8(entityList8);
	Ifc4::IfcRelAssociatesMaterial* ifcRelAssociatesMaterial = new Ifc4::IfcRelAssociatesMaterial(guid::IfcGloballyUniqueId("ceva"), file.getSingle<Ifc4::IfcOwnerHistory>(),
		boost::none, boost::none, unitEntity8, ifcMaterial);
	file.addEntity(ifcRelAssociatesMaterial);
}


void IfcMaterialEnhancer::processMaterial(ReaderPropertyDefinition& readerPropertyDefinition, IfcHierarchyHelper<Ifc4>& file,Ifc4::IfcElement* ifcElement) {
	typedef Ifc4::IfcGloballyUniqueId guid;

	Ifc4::IfcMaterial* ifcMaterial = new Ifc4::IfcMaterial("Material", boost::none, boost::none);


	IfcEntityList* entityList8 = new IfcEntityList();
	entityList8->push(ifcElement);
	boost::shared_ptr<IfcEntityList> unitEntity8(entityList8);
	Ifc4::IfcRelAssociatesMaterial* ifcRelAssociatesMaterial = new Ifc4::IfcRelAssociatesMaterial(guid::IfcGloballyUniqueId("ceva"), file.getSingle<Ifc4::IfcOwnerHistory>(),
		boost::none, boost::none, unitEntity8, ifcMaterial);
	file.addEntity(ifcRelAssociatesMaterial);
}

Ifc4::IfcColourRgb* IfcMaterialEnhancer::parseAndCreateColour(std::string colourValue)
{
	std::string colourName = "Colour";
	std::string result;
	try {
		std::regex re("\\[\\d+\\,\\d+\\,\\d+\\]");
		std::smatch match;
		if (std::regex_search(colourValue, match, re) && match.size() > 0) {
			result = match.str(0);
		}
		else {
			result = std::string("");
		}
	}
	catch (std::regex_error& e) {
		e.code();
	}

	if (result.empty()) {
		return new Ifc4::IfcColourRgb(colourName, 0.6, 0.6, 0.6);;
	}
	result = result.substr(1, result.size() - 2);

	std::vector<int> colors;

	std::stringstream s_stream(result); 
	while (s_stream.good()) {
		std::string substr;
		std::getline(s_stream, substr, ',');
		int intValue = std::stoi(substr);
		if (intValue >= 0 && intValue <= 255) {
			colors.push_back(intValue);
		}
		
	}

	if (colors.size() == 3) {
		return new Ifc4::IfcColourRgb(colourName,colors.at(0)/255, colors.at(1)/255, colors.at(2)/255);
	}
	
	return new Ifc4::IfcColourRgb(colourName, 1, 1, 0);
}
