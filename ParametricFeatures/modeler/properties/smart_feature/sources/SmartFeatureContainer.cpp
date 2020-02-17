#include "../headers/SmartFeatureContainer.h"

void SmartFeatureContainer::insertNodeInTree(long newCurrentElementId, long newLocalNodeId, long newParentLocalNodeId, long newElementId)
{
	if (this->root == nullptr || newParentLocalNodeId <= 0) {
		this->root = new SmartFeatureTreeNode();
		this->root->getSmartFeatureProperties()->setElementId(newElementId);
		this->root->getSmartFeatureProperties()->setLocalNodeId(newLocalNodeId);
		this->root->getSmartFeatureProperties()->setLocalParentNodeId(-1);
		this->root->getSmartFeatureProperties()->setCurrentElementId(newCurrentElementId);
	}
	else {
		SmartFeatureTreeNode* parent = search(this->root, newParentLocalNodeId);
		if (parent != nullptr) {

			SmartFeatureTreeNode* newNode = new SmartFeatureTreeNode();
			newNode->getSmartFeatureProperties()->setElementId(newElementId);
			newNode->getSmartFeatureProperties()->setLocalNodeId(newLocalNodeId);
			newNode->getSmartFeatureProperties()->setLocalParentNodeId(newParentLocalNodeId);
			newNode->getSmartFeatureProperties()->setCurrentElementId(newCurrentElementId);

			if (parent->getLeftNode() == nullptr) {

				parent->setLeftNode(newNode);
			}
			else if (parent->getRightNode() == nullptr) {
				parent->setRightNode(newNode);
			}
			else {
				// TODO log exception/warning
			}
		}
	}
}

SmartFeatureTreeNode * SmartFeatureContainer::search(SmartFeatureTreeNode * searchNode, long searchLocalId)
{
	if (searchNode == nullptr) {
		return nullptr;
	}
	if (searchNode->getSmartFeatureProperties()->getLocalNodeId() == searchLocalId) {
		return searchNode;
	}

	SmartFeatureTreeNode* leftNode = search(searchNode->getLeftNode(), searchLocalId);
	if (leftNode != nullptr) {
		return leftNode;
	}
	SmartFeatureTreeNode* rightNode = search(searchNode->getRightNode(), searchLocalId);
	if (rightNode != nullptr) {
		return rightNode;
	}

	return nullptr;
}

SmartFeatureTreeNode * SmartFeatureContainer::getRoot()
{
	return this->root;
}
