#include "../headers/IfcMaterialEnhancer.h"

void IfcMaterialEnhancer::enhanceMaterials(std::vector<DictionaryProperties*>& dictionaryPropertiesVector, std::vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file)
{

	if (!dictionaryPropertiesVector.empty())
	{
		for (int i = 0; i < dictionaryPropertiesVector.size(); i++)
		{
			DictionaryProperties& dictionaryProperties = *dictionaryPropertiesVector.at(i);

			// TODO [MP] to be replaced with method to check by id. order doesnt guarantee that it's the correct element
			IfcElementBundle*& ifcElementBundle = ifcBundleVector.at(i);

			Ifc4::IfcObjectDefinition::list::ptr ifcObjectDefinitionList(new Ifc4::IfcObjectDefinition::list());
			ifcObjectDefinitionList->push(ifcElementBundle->getIfcElement());
			//IfcTemplatedEntityList<Ifc4::IfcElement>* templatedList2 = new IfcTemplatedEntityList<Ifc4::IfcElement>();

			for (auto const& readerPropertyBundle : dictionaryProperties.getReaderPropertiesBundleVector()) {
				processMaterials(*readerPropertyBundle,file, *ifcElementBundle);
			}
		}
	}
}

void IfcMaterialEnhancer::processMaterials(ReaderPropertiesBundle& readerPropertiesBundle, IfcHierarchyHelper<Ifc4>& file, IfcElementBundle& ifcElementBundle)
{
	for (auto const& readerPropertyDefinition : readerPropertiesBundle.getProperties()) {
		if (readerPropertyDefinition->getPropertyName().find("Color") != std::string::npos) {
			processColour(*readerPropertyDefinition,file, ifcElementBundle);
		} else 	if (readerPropertyDefinition->getPropertyName().find("Material") != std::string::npos) {
			processMaterial(*readerPropertyDefinition,file, ifcElementBundle.getIfcElement());
		}
	}
}

void IfcMaterialEnhancer::processColour(ReaderPropertyDefinition& readerPropertyDefinition, IfcHierarchyHelper<Ifc4>& file, IfcElementBundle& ifcElementBundle)
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

	for (int i = 0; i < ifcElementBundle.getIfcGraphicPropertiesBundleVector().size(); ++i) {
		Ifc4::IfcStyledItem* ifcStyledItem = new Ifc4::IfcStyledItem(ifcElementBundle.getIfcGraphicPropertiesBundleVector().at(i)->getIfcRepresentationItem(), IfcPresentationStyleAssignmentList, boost::none);
		file.addEntity(ifcStyledItem);
		styledItemList->push(ifcStyledItem);
	}

	Ifc4::IfcStyledItem* ifcStyledItem = new Ifc4::IfcStyledItem(ifcElementBundle.getIfcGraphicPropertiesBundleVector().at(0)->getIfcRepresentationItem(), IfcPresentationStyleAssignmentList, boost::none);
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
	entityList8->push(ifcElementBundle.getIfcElement());
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
		return nullptr;
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

	std::string colourName = "Colour";
	if (colors.size() == 3) {
		return new Ifc4::IfcColourRgb(colourName,colors.at(0)/255, colors.at(1)/255, colors.at(2)/255);
	}
	
	return new Ifc4::IfcColourRgb(colourName, 1, 1, 0);
}
