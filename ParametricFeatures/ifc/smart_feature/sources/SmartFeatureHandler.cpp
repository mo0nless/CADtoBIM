#include "../headers/SmartFeatureHandler.h"

void SmartFeatureHandler::handleSmartFeature(std::vector<IfcBundle*>& ifcBundleVector)
{
	for (auto ifcBundle : ifcBundleVector) {
		if (ifcBundle->getIsSmartFeature()) {
			Ifc4::IfcRepresentationItem* ifcResult = eval(ifcBundle->getSmartFeatureContainer()->getRoot(), ifcBundleVector, ifcBundle);
			ifcBundle->addIfcGraphicPropertiesBundle(new IfcGraphicPropertiesBundle(new GraphicProperties(), ifcResult));
		}
	}
}


Ifc4::IfcRepresentationItem* SmartFeatureHandler::eval(SmartFeatureTreeNode* root, std::vector<IfcBundle*>& ifcBundleVector, IfcBundle* currentElement)
{
	// empty tree  
	if (!root)
		return nullptr;

	// leaf node i.e, an integer  
	if (root->getLeftNode() == nullptr && root->getRightNode() == nullptr) {
		IfcBundle* foundBundle = getIfcBundleByGlobalId(ifcBundleVector, root->getGlobalNodeId());
		if (foundBundle != nullptr && !foundBundle->getIfcGraphicPropertiesBundleVector().empty()) {
			return foundBundle->getIfcGraphicPropertiesBundleVector().at(0)->getIfcRepresentationItem();
		}
		else {
			return nullptr;
		}

	}
	Ifc4::IfcRepresentationItem* left = nullptr, *rigth = nullptr;
	if (root->getLeftNode() != nullptr) {
		left = eval(root->getLeftNode(), ifcBundleVector, currentElement);
	}
	if (root->getRightNode() != nullptr) {
		rigth = eval(root->getRightNode(), ifcBundleVector, currentElement);
	}

	IfcReaderPropertiesBundle* ifcReaderPropertiesBundle = getIfcReaderPropertiesBundleByLocalId(*currentElement, root->getLocalNodeId());
	if (ifcReaderPropertiesBundle!=nullptr && ifcReaderPropertiesBundle->getReaderPropertiesBundle()->getCassName() == "BooleanFeature" && left != nullptr && rigth != nullptr) {
		Ifc4::IfcRepresentationItem* resultItem = IfcBooleanOperatorHandler::solveBooleanOperaiont(left, rigth,*ifcReaderPropertiesBundle);
		return resultItem;
	}
		

	return nullptr;

}

IfcBundle* SmartFeatureHandler::getIfcBundleByGlobalId(std::vector<IfcBundle*>& ifcBundleVector, int globalId) {
	if (globalId < 0) {
		return nullptr;
	}
	for (auto const& ifcBundle : ifcBundleVector) {
		if (ifcBundle->getModelerElementId() == globalId) {
			if (!ifcBundle->getIsSmartFeature()) {
				ifcBundle->getIfcGraphicPropertiesBundleVector().at(0)->setShow(false);
			}
			return ifcBundle;
		}
	}
	return nullptr;
}

IfcReaderPropertiesBundle* SmartFeatureHandler::getIfcReaderPropertiesBundleByLocalId(IfcBundle& ifcBundle, int localId) {

	for (auto const& readerProperty : ifcBundle.getIfcReaderPropertiesBundleVector()) {
		if (readerProperty!=nullptr && readerProperty->getReaderPropertiesBundle()!=nullptr && readerProperty->getReaderPropertiesBundle()->getLocalId() == localId) {
			return readerProperty;
		}
	}
	
	return nullptr;
}