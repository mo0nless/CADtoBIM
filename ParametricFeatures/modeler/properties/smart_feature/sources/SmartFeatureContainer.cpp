#include "../headers/SmartFeatureContainer.h"

SmartFeatureContainer::SmartFeatureContainer()
{
	this->mRoot = nullptr;
}


void SmartFeatureContainer::insertNodeInTree(long newCurrentElementId, long newLocalNodeId, long newParentLocalNodeId, long newLeafElementId)
{
	if (this->mRoot == nullptr || newParentLocalNodeId <= 0) {
		this->mRoot = new SmartFeatureTreeNode();
		this->mRoot->getGeneralProperties()->setElementId(newLeafElementId);
		this->mRoot->getReaderProperties()->getSmartFeatureGeneralProperties()->setLocalNodeId(newLocalNodeId);
		this->mRoot->getReaderProperties()->getSmartFeatureGeneralProperties()->setLocalParentNodeId(-1);
		this->mRoot->getGeneralProperties()->setCurrentElementId(newCurrentElementId);
		this->mRoot->getGeneralProperties()->setIsSmartFeature(true);
	}
	else {
		SmartFeatureTreeNode* parent = searchByElementLocalNodeId(this->mRoot, newParentLocalNodeId);
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
	return this->mRoot;
}
