#include "../headers/SmartFeatureHandler.h"

void SmartFeatureHandler::handleSmartFeature(std::vector<IfcElementBundle*>& ifcBundleVector)
{
	for (auto ifcBundle : ifcBundleVector) {
		if (ifcBundle->getIsSmartFeature()) {
			//Ifc4::IfcRepresentationItem* ifcResult = eval(ifcBundle->getSmartFeatureContainer()->getRoot(), ifcBundleVector, ifcBundle);
			Ifc4::IfcGeometricRepresentationItem* ifcResult = eval(ifcBundle->getSmartFeatureContainer()->getRoot(), ifcBundleVector, ifcBundle);
			// TODO [MP] keep the existing graphic properties and only add the ifc representation item
			ifcBundle->addIfcGraphicPropertiesBundle(new IfcGraphicPropertiesBundle(new GraphicProperties(), ifcResult));
		}
	}
}


Ifc4::IfcGeometricRepresentationItem* SmartFeatureHandler::eval(SmartFeatureTreeNode* root, std::vector<IfcElementBundle*>& ifcBundleVector, IfcElementBundle* currentElement)
{
	if (!root)
		return nullptr;

	if (root->getLeftNode() == nullptr && root->getRightNode() == nullptr) {
		IfcElementBundle* foundBundle = getIfcBundleByGlobalId(ifcBundleVector, root->getGlobalNodeId());
		if (foundBundle != nullptr && !foundBundle->getIfcGraphicPropertiesBundleVector().empty()) {
			return foundBundle->getIfcGraphicPropertiesBundleVector().at(0)->getIfcRepresentationItem();
		}
		else {
			return nullptr;
		}

	}
	Ifc4::IfcGeometricRepresentationItem* left = nullptr, *rigth = nullptr;
	if (root->getLeftNode() != nullptr) {
		left = eval(root->getLeftNode(), ifcBundleVector, currentElement);
	}
	if (root->getRightNode() != nullptr) {
		rigth = eval(root->getRightNode(), ifcBundleVector, currentElement);
	}

	IfcReaderPropertiesBundle* ifcReaderPropertiesBundle = getIfcReaderPropertiesBundleByLocalId(*currentElement, root->getLocalNodeId());
	if (ifcReaderPropertiesBundle!=nullptr && ifcReaderPropertiesBundle->getReaderPropertiesBundle()->getCassName() == "BooleanFeature" && left != nullptr && rigth != nullptr) {
		Ifc4::IfcGeometricRepresentationItem* resultItem = IfcBooleanOperatorHandler::solveBooleanOperation(left, rigth,*ifcReaderPropertiesBundle);
		return resultItem;
	}
		

	return nullptr;

}

IfcElementBundle* SmartFeatureHandler::getIfcBundleByGlobalId(std::vector<IfcElementBundle*>& ifcBundleVector, int globalId) {
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

IfcReaderPropertiesBundle* SmartFeatureHandler::getIfcReaderPropertiesBundleByLocalId(IfcElementBundle& ifcBundle, int localId) {

	for (auto const& readerProperty : ifcBundle.getIfcReaderPropertiesBundleVector()) {
		if (readerProperty!=nullptr && readerProperty->getReaderPropertiesBundle()!=nullptr && readerProperty->getReaderPropertiesBundle()->getLocalId() == localId) {
			return readerProperty;
		}
	}
	
	return nullptr;
}