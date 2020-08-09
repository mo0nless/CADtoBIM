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

			for (auto const& readerPropertyBundle : dictionaryProperties.getElementReaderPropertiesBundleVector()) {
				processMaterials(*readerPropertyBundle, file, *ifcElementBundle);
			}

			for (auto const& elem : dictionaryProperties.getElementBundle()) {
				processMaterials(*elem->getReaderPropertiesBundle(), file, *ifcElementBundle);
			}


			//IfcTemplatedEntityList<Ifc4::IfcElement>* templatedList2 = new IfcTemplatedEntityList<Ifc4::IfcElement>();

			//if (!dictionaryProperties.getGraphicsReaderPropertiesBundleVector().empty()) {
			//	for (auto const& readerPropertyBundle : dictionaryProperties.getGraphicsReaderPropertiesBundleVector()) {
			//		processMaterials(*readerPropertyBundle, file, *ifcElementBundle);
			//	}
			//}
			//else {
			//	for (auto const& readerPropertyBundle : dictionaryProperties.getElementReaderPropertiesBundleVector()) {
			//		processMaterials(*readerPropertyBundle, file, *ifcElementBundle);
			//	}
			//}

		}
	}
}

void IfcMaterialEnhancer::processMaterials(ReaderPropertiesBundle& readerPropertiesBundle, IfcHierarchyHelper<Ifc4>& file, IfcElementBundle& ifcElementBundle)
{
	for (auto const& readerPropertyDefinition : readerPropertiesBundle.getProperties()) {
		if (readerPropertyDefinition->getPropertyName().find("Material") != std::string::npos) {
			processMaterial(*readerPropertyDefinition,file, ifcElementBundle.getIfcElement());
		}
	}
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
	//return new Ifc4::IfcColourRgb(std::string("Colour"), 0.6, 0.6, 0.6);

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
		int intValue;
		try {
			intValue = std::stoi(colourValue);
		}
		catch (std::exception& e) {
			e.what();
		}
		if (intValue > 0) {
			int blue = (intValue >> 16) & 0xFF;
			int green = (intValue >> 8) & 0xFF;
			int red = intValue & 0xFF;

			double red1 = red*1.0;
			double green1 = green*1.0;
			double blue1 = blue*1.0;

			return new Ifc4::IfcColourRgb(colourName, red1/255.0, green1/255.0, blue1/255.0);
		}
		else {
			return new Ifc4::IfcColourRgb(colourName, 0.6, 0.6, 0.6);
		}
		
	}
	result = result.substr(1, result.size() - 2);

	std::vector<double> colors;

	std::stringstream s_stream(result); 
	while (s_stream.good()) {
		std::string substr;
		std::getline(s_stream, substr, ',');
		double doubleValue = std::stod(substr);
		if (doubleValue >= 0.0 && doubleValue <= 255.0) {
			colors.push_back(doubleValue);
		}
		
	}

	if (colors.size() == 3) {
		return new Ifc4::IfcColourRgb(colourName,colors.at(0)/255, colors.at(1)/255, colors.at(2)/255);
	}
	
	return new Ifc4::IfcColourRgb(colourName, 1, 1, 0);
}
