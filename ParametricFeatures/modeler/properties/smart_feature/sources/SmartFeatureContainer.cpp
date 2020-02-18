#include "../headers/SmartFeatureContainer.h"

void SmartFeatureContainer::insertNodeInTree(long newCurrentElementId, long newLocalNodeId, long newParentLocalNodeId, long newElementId)
{
	if (this->root == nullptr || newParentLocalNodeId <= 0) {
		this->root = new SmartFeatureTreeNode();
		this->root->getGeneralProperties()->setElementId(newElementId);
		this->root->getGeneralProperties()->setLocalNodeId(newLocalNodeId);
		this->root->getGeneralProperties()->setLocalParentNodeId(-1);
		this->root->getGeneralProperties()->setCurrentElementId(newCurrentElementId);
	}
	else {
		SmartFeatureTreeNode* parent = searchByLocalId(this->root, newParentLocalNodeId);
		if (parent != nullptr) {

			SmartFeatureTreeNode* newNode = new SmartFeatureTreeNode();
			newNode->getGeneralProperties()->setElementId(newElementId);
			newNode->getGeneralProperties()->setLocalNodeId(newLocalNodeId);
			newNode->getGeneralProperties()->setLocalParentNodeId(newParentLocalNodeId);
			newNode->getGeneralProperties()->setCurrentElementId(newCurrentElementId);

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

SmartFeatureTreeNode * SmartFeatureContainer::searchByLocalId(SmartFeatureTreeNode * searchNode, long searchedLocalId)
{
	if (searchNode == nullptr || searchedLocalId<=0) {
		return nullptr;
	}
	if (searchNode->getGeneralProperties()->getLocalNodeId() == searchedLocalId) {
		return searchNode;
	}

	SmartFeatureTreeNode* leftNode = searchByLocalId(searchNode->getLeftNode(), searchedLocalId);
	if (leftNode != nullptr) {
		return leftNode;
	}
	SmartFeatureTreeNode* rightNode = searchByLocalId(searchNode->getRightNode(), searchedLocalId);
	if (rightNode != nullptr) {
		return rightNode;
	}

	return nullptr;
}

SmartFeatureTreeNode * SmartFeatureContainer::searchByElementId(SmartFeatureTreeNode * searchNode, long searchedElementId)
{
	if (searchNode == nullptr || searchedElementId <=0) {
		return nullptr;
	}
	if (searchNode->getGeneralProperties()->getElementId() == searchedElementId) {
		return searchNode;
	}

	SmartFeatureTreeNode* leftNode = searchByElementId(searchNode->getLeftNode(), searchedElementId);
	if (leftNode != nullptr) {
		return leftNode;
	}
	SmartFeatureTreeNode* rightNode = searchByElementId(searchNode->getRightNode(), searchedElementId);
	if (rightNode != nullptr) {
		return rightNode;
	}

	return nullptr;
}

SmartFeatureTreeNode * SmartFeatureContainer::getRoot()
{
	return this->root;
}
