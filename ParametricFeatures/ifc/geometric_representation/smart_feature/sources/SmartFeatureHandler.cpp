#include "../headers/SmartFeatureHandler.h"

#pragma warning (disable:4311 4302 4312 4189)
void SmartFeatureHandler::handleSmartFeature(vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file)
{
	for (auto ifcElementBundle : ifcBundleVector) {
		if (ifcElementBundle->getIsSmartFeature()) {
			SmartFeatureContainer* container = ifcElementBundle->getSmartFeatureContainer();
			IfcElementBundle* ifcResult = eval(container->getRoot(), ifcBundleVector, ifcElementBundle,file);

			if (ifcResult != nullptr) {
				auto ifcGraphicPropertiesBundle = new IfcGraphicPropertiesBundle(
					new GraphicProperties(),
					ifcResult->getIfcGraphicPropertiesBundleVector().at(0)->getIfcRepresentationItem()
				);
				ifcGraphicPropertiesBundle->setRepresentationTypeIdentifier("CSG", "Body");
				ifcElementBundle->addIfcGraphicPropertiesBundle(ifcGraphicPropertiesBundle);
			}
			
		}
	}
}


IfcElementBundle* SmartFeatureHandler::eval(SmartFeatureTreeNode* root, vector<IfcElementBundle*>& ifcBundleVector, IfcElementBundle* smartFeature, IfcHierarchyHelper<Ifc4>& file)
{
	if (!root)
		return nullptr;

	if (root->getLeftNode() == nullptr && root->getRightNode() == nullptr) {
		return getIfcBundleByGlobalId(ifcBundleVector, root->getGlobalNodeId());
	}
	IfcElementBundle *left = nullptr, *right = nullptr;
	if (root->getLeftNode() != nullptr) {
		left = eval(root->getLeftNode(), ifcBundleVector, smartFeature,file);
	}
	if (root->getRightNode() != nullptr) {
		right = eval(root->getRightNode(), ifcBundleVector, smartFeature,file);
	}

	IfcReaderPropertiesBundle* ifcReaderPropertiesBundle = getIfcReaderPropertiesBundleByLocalId(*smartFeature, root->getLocalNodeId());
	if (ifcReaderPropertiesBundle!=nullptr && ifcReaderPropertiesBundle->getClassName() == "BooleanFeature" && 
		left != nullptr && right != nullptr) {
		Ifc4::IfcGeometricRepresentationItem* result =  IfcSolidsOperationBuilder::solveBooleanOperation(
			left->getIfcGraphicPropertiesBundleVector().at(0)->getIfcRepresentationItem(),
			right->getIfcGraphicPropertiesBundleVector().at(0)->getIfcRepresentationItem(),
			*ifcReaderPropertiesBundle);
		IfcElementBundle* temp = new IfcElementBundle(-1, "BooleanFeature");

		temp->addIfcGraphicPropertiesBundle(new IfcGraphicPropertiesBundle(new GraphicProperties(), result));
		return temp;
	}
	else if (ifcReaderPropertiesBundle != nullptr && 
		CreateSolidFunctionsEnumUtils::getCreateSolidFunctionsEnumByClassName(ifcReaderPropertiesBundle->getClassName()) != CreateSolidFunctionsEnum::UNDEFINED &&
		(left != nullptr || right != nullptr)) {
			Ifc4::IfcGeometricRepresentationItem* result = IfcSolidsOperationBuilder::buildIfcCreateSolidsOperation(left, right, *ifcReaderPropertiesBundle,file);
			IfcElementBundle* temp = new IfcElementBundle(-1, "CreatedSolid");

			temp->addIfcGraphicPropertiesBundle(new IfcGraphicPropertiesBundle(new GraphicProperties(), result));
			return temp;
	}
	
	return nullptr;

}

IfcElementBundle* SmartFeatureHandler::getIfcBundleByGlobalId(vector<IfcElementBundle*>& ifcBundleVector, int globalId) {
	if (globalId < 0) {
		return nullptr;
	}
	for (auto const& ifcBundle : ifcBundleVector) {
		if (ifcBundle->getElementId() == globalId) {
			if (!ifcBundle->getIsSmartFeature() && ifcBundle->getIfcGraphicPropertiesBundleVector().size()>0) {
				//Flag as not displayable object
				ifcBundle->getIfcGraphicPropertiesBundleVector().at(0)->setShow(false);
			}
			return ifcBundle;
		}
	}
	return nullptr;
}

IfcReaderPropertiesBundle* SmartFeatureHandler::getIfcReaderPropertiesBundleByLocalId(IfcElementBundle& ifcBundle, int localId) {

	for (auto const& readerProperty : ifcBundle.getIfcElementReaderPropertiesBundleVector()) {
		if (readerProperty!=nullptr && readerProperty->getLocalId() == localId) {
			return readerProperty;
		}
	}
	
	return nullptr;
}
#pragma warning(pop)