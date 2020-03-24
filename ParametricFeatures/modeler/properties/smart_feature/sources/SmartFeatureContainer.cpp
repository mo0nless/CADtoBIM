#include "../headers/SmartFeatureContainer.h"

SmartFeatureContainer::SmartFeatureContainer()
{
	this->pRoot = nullptr;
}


void SmartFeatureContainer::insertNodeInTree(long newCurrentElementId, long newLocalNodeId, long newParentLocalNodeId, long newLeafElementId)
{
	if (this->pRoot == nullptr || newParentLocalNodeId <= 0) {
		this->pRoot = new SmartFeatureTreeNode();
		this->pRoot->getGeneralProperties()->setElementId(newLeafElementId);
		this->pRoot->getReaderProperties()->getSmartFeatureGeneralProperties()->setLocalNodeId(newLocalNodeId);
		this->pRoot->getReaderProperties()->getSmartFeatureGeneralProperties()->setLocalParentNodeId(-1);
		this->pRoot->getGeneralProperties()->setCurrentElementId(newCurrentElementId);
		this->pRoot->getGeneralProperties()->setIsSmartFeature(true);
	}
	else {
		SmartFeatureTreeNode* parent = searchByElementLocalNodeId(this->pRoot, newParentLocalNodeId);
		if (parent != nullptr) {

			SmartFeatureTreeNode* newNode = new SmartFeatureTreeNode();
			newNode->getGeneralProperties()->setElementId(newLeafElementId);
			newNode->getReaderProperties()->getSmartFeatureGeneralProperties()->setLocalNodeId(newLocalNodeId);
			newNode->getReaderProperties()->getSmartFeatureGeneralProperties()->setLocalParentNodeId(newParentLocalNodeId);
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
	if (searchNode->getReaderProperties()->getSmartFeatureGeneralProperties()->getLocalNodeId() == searchedLocalId) {
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
	return this->pRoot;
}
