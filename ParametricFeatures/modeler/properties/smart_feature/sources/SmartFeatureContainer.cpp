#include "../headers/SmartFeatureContainer.h"



SmartFeatureContainer::SmartFeatureContainer(long newElementId)
{
	this->elementId = newElementId;
	this->root = nullptr;
}

void SmartFeatureContainer::insertNodeInTree(long newLocalNodeId, long newParentLocalNodeId, long newGlobalNodeid)
{
	if (this->root == nullptr || newParentLocalNodeId <= 0) 
	{
		this->root = new SmartFeatureTreeNode(newGlobalNodeid, newLocalNodeId, -1);
		//this->pRoot->getGeneralProperties()->setElementId(newGlobalNodeid);
		//this->pRoot->getReaderProperties()->getSmartFeatureGeneralProperties()->setLocalNodeId(newLocalNodeId);
		//this->pRoot->getReaderProperties()->getSmartFeatureGeneralProperties()->setLocalParentNodeId(-1);
		//this->pRoot->getGeneralProperties()->setCurrentElementId(newCurrentElementId);
		//this->pRoot->getGeneralProperties()->setIsSmartFeature(true);
	}
	else 
	{
		SmartFeatureTreeNode* parent = searchByElementLocalNodeId(this->root, newParentLocalNodeId);
		if (parent != nullptr) {

			SmartFeatureTreeNode* newNode = new SmartFeatureTreeNode(newGlobalNodeid, newLocalNodeId, newParentLocalNodeId);
			//newNode->getGeneralProperties()->setElementId(newGlobalNodeid);
			//newNode->getReaderProperties()->getSmartFeatureGeneralProperties()->setLocalNodeId(newLocalNodeId);
			//newNode->getReaderProperties()->getSmartFeatureGeneralProperties()->setLocalParentNodeId(newParentLocalNodeId);
			//newNode->getGeneralProperties()->setCurrentElementId(newCurrentElementId);
			//newNode->getGeneralProperties()->setIsSmartFeature(true);

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
		int leftNodeDepth = getTreeMaxDepth(treeNode->getLeftNode());
		int rightNodeDepth = getTreeMaxDepth(treeNode->getRightNode());

		if (leftNodeDepth > rightNodeDepth) return(leftNodeDepth + 1);
		else return(rightNodeDepth + 1);
	}
}

SmartFeatureTreeNode * SmartFeatureContainer::searchByElementLocalNodeId(SmartFeatureTreeNode * searchNode, long searchedLocalNodeId)
{
	if (searchNode == nullptr || searchedLocalNodeId<=0) {
		return nullptr;
	}
	if (searchNode->getLocalNodeId() == searchedLocalNodeId) {
		return searchNode;
	}

	SmartFeatureTreeNode* leftNode = searchByElementLocalNodeId(searchNode->getLeftNode(), searchedLocalNodeId);
	if (leftNode != nullptr) {
		return leftNode;
	}
	SmartFeatureTreeNode* rightNode = searchByElementLocalNodeId(searchNode->getRightNode(), searchedLocalNodeId);
	if (rightNode != nullptr) {
		return rightNode;
	}

	return nullptr;
}

SmartFeatureTreeNode * SmartFeatureContainer::searchByElementGlobalId(SmartFeatureTreeNode * searchNode, long searchedGlobalNodeId)
{
	if (searchNode == nullptr || searchedGlobalNodeId <=0) {
		return nullptr;
	}
	if (searchNode->getGlobalNodeId() == searchedGlobalNodeId) {
		return searchNode;
	}

	SmartFeatureTreeNode* leftNode = searchByElementGlobalId(searchNode->getLeftNode(), searchedGlobalNodeId);
	if (leftNode != nullptr) {
		return leftNode;
	}
	SmartFeatureTreeNode* rightNode = searchByElementGlobalId(searchNode->getRightNode(), searchedGlobalNodeId);
	if (rightNode != nullptr) {
		return rightNode;
	}

	return nullptr;
}

SmartFeatureTreeNode * SmartFeatureContainer::getRoot()
{
	return this->root;
}

long SmartFeatureContainer::getElementId()
{
	return this->elementId;
}
