#include "../headers/SmartFeatureHandler.h"

void SmartFeatureHandler::handleSmartFeature(std::vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file)
{
	for (auto ifcBundle : ifcBundleVector) {
		if (ifcBundle->getIsSmartFeature()) {
			IfcElementBundle* ifcResult = eval(ifcBundle->getSmartFeatureContainer()->getRoot(), ifcBundleVector, ifcBundle,file);
			// TODO [MP] keep the existing graphic properties and only add the ifc representation item
			//ifcBundle->addIfcGraphicPropertiesBundle(new IfcGraphicPropertiesBundle(new GraphicProperties(), ifcResult));
			ifcBundle->addIfcGraphicPropertiesBundle(new IfcGraphicPropertiesBundle(new GraphicProperties(), ifcResult->getIfcGraphicPropertiesBundleVector().at(0)->getIfcRepresentationItem()));
		}
	}
}


IfcElementBundle* SmartFeatureHandler::eval(SmartFeatureTreeNode* root, std::vector<IfcElementBundle*>& ifcBundleVector, IfcElementBundle* smartFeature, IfcHierarchyHelper<Ifc4>& file)
{
	if (!root)
		return nullptr;

	if (root->getLeftNode() == nullptr && root->getRightNode() == nullptr) {
		return getIfcBundleByGlobalId(ifcBundleVector, root->getGlobalNodeId());
	}
	IfcElementBundle *left = nullptr, *rigth = nullptr;
	if (root->getLeftNode() != nullptr) {
		left = eval(root->getLeftNode(), ifcBundleVector, smartFeature,file);
	}
	if (root->getRightNode() != nullptr) {
		rigth = eval(root->getRightNode(), ifcBundleVector, smartFeature,file);
	}

	IfcReaderPropertiesBundle* ifcReaderPropertiesBundle = getIfcReaderPropertiesBundleByLocalId(*smartFeature, root->getLocalNodeId());
	if (ifcReaderPropertiesBundle!=nullptr && ifcReaderPropertiesBundle->getReaderPropertiesBundle()->getCassName() == "BooleanFeature" && left != nullptr && rigth != nullptr) {
		Ifc4::IfcGeometricRepresentationItem* result =  IfcBooleanOperatorHandler::solveBooleanOperation(left->getIfcGraphicPropertiesBundleVector().at(0)->getIfcRepresentationItem(),
			rigth->getIfcGraphicPropertiesBundleVector().at(0)->getIfcRepresentationItem(),*ifcReaderPropertiesBundle);
		IfcElementBundle* temp = new IfcElementBundle(-1, "temp");
		temp->addIfcGraphicPropertiesBundle(new IfcGraphicPropertiesBundle(new GraphicProperties(), result));
		return temp;
	}
	else if (ifcReaderPropertiesBundle != nullptr && 
		CreateSolidFunctionsEnumUtils::getCreateSolidFunctionsEnumByClassName(ifcReaderPropertiesBundle->getReaderPropertiesBundle()->getCassName()) != CreateSolidFunctionsEnum::UNDEFINED &&
		(left != nullptr || rigth != nullptr)) {
		Ifc4::IfcGeometricRepresentationItem* result = IfcCreateSolidsOperationBuilder::buildIfcCreateSolidsOperation(left, rigth, *ifcReaderPropertiesBundle,file);
		IfcElementBundle* temp = new IfcElementBundle(-1, "temp");
		temp->addIfcGraphicPropertiesBundle(new IfcGraphicPropertiesBundle(new GraphicProperties(), result));
		return temp;
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