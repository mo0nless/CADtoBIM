#include "../headers/SmartFeatureContainer.h"

SmartFeatureContainer::SmartFeatureContainer()
{
	this->root = nullptr;
}

void SmartFeatureContainer::insertNodeInTree(long newCurrentElementId, long newLocalNodeId, long newParentLocalNodeId, long newElementId)
{
	if (this->root == nullptr || newParentLocalNodeId <= 0) {
		this->root = new SmartFeatureTreeNode();
		this->root->getGeneralProperties()->setElementId(newElementId);
		this->root->getGeneralProperties()->setLocalNodeId(newLocalNodeId);
		this->root->getGeneralProperties()->setLocalParentNodeId(-1);
		this->root->getGeneralProperties()->setCurrentElementId(newCurrentElementId);
		this->root->getGeneralProperties()->setIsSmartFeature(true);
	}
	else {
		SmartFeatureTreeNode* parent = searchByElementLocalNodeId(this->root, newParentLocalNodeId);
		if (parent != nullptr) {

			SmartFeatureTreeNode* newNode = new SmartFeatureTreeNode();
			newNode->getGeneralProperties()->setElementId(newElementId);
			newNode->getGeneralProperties()->setLocalNodeId(newLocalNodeId);
			newNode->getGeneralProperties()->setLocalParentNodeId(newParentLocalNodeId);
			newNode->getGeneralProperties()->setCurrentElementId(newCurrentElementId);
			newNode->getGeneralProperties()->setIsSmartFeature(true);

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

int SmartFeatureContainer::getTreeMaxDepth(SmartFeatureTreeNode* treeNode)
{
	if (treeNode == nullptr)
	{
		return 0;
	}
	else
	{
		int lDepth = getTreeMaxDepth(treeNode->getLeftNode());
		int rDepth = getTreeMaxDepth(treeNode->getRightNode());

		if (lDepth > rDepth) return(lDepth + 1);
		else return(rDepth + 1);
	}
}

SmartFeatureTreeNode * SmartFeatureContainer::searchByElementLocalNodeId(SmartFeatureTreeNode * searchNode, long searchedLocalId)
{
	if (searchNode == nullptr || searchedLocalId<=0) {
		return nullptr;
	}
	if (searchNode->getGeneralProperties()->getLocalNodeId() == searchedLocalId) {
		return searchNode;
	}

	SmartFeatureTreeNode* leftNode = searchByElementLocalNodeId(searchNode->getLeftNode(), searchedLocalId);
	if (leftNode != nullptr) {
		return leftNode;
	}
	SmartFeatureTreeNode* rightNode = searchByElementLocalNodeId(searchNode->getRightNode(), searchedLocalId);
	if (rightNode != nullptr) {
		return rightNode;
	}

	return nullptr;
}

SmartFeatureTreeNode * SmartFeatureContainer::searchByElementGlobalId(SmartFeatureTreeNode * searchNode, long searchedElementId)
{
	if (searchNode == nullptr || searchedElementId <=0) {
		return nullptr;
	}
	if (searchNode->getGeneralProperties()->getElementId() == searchedElementId) {
		return searchNode;
	}

	SmartFeatureTreeNode* leftNode = searchByElementGlobalId(searchNode->getLeftNode(), searchedElementId);
	if (leftNode != nullptr) {
		return leftNode;
	}
	SmartFeatureTreeNode* rightNode = searchByElementGlobalId(searchNode->getRightNode(), searchedElementId);
	if (rightNode != nullptr) {
		return rightNode;
	}

	return nullptr;
}

SmartFeatureTreeNode * SmartFeatureContainer::getRoot()
{
	return this->root;
}
