#include "../headers/SmartFeatureTreeNode.h"


SmartFeatureTreeNode::SmartFeatureTreeNode(long newGlobalNodeId, long newLocalNodeId, long newLocalParentNodeId)
{
	this->globalNodeId = newGlobalNodeId;
	this->localNodeId = newLocalNodeId;
	this->localParentNodeId = newLocalParentNodeId;
	
	this->rightNode = nullptr;
	this->leftNode = nullptr;
}

void SmartFeatureTreeNode::setLeftNode(SmartFeatureTreeNode* newLeftNode)
{
	this->leftNode = newLeftNode;
}

void SmartFeatureTreeNode::setRightNode(SmartFeatureTreeNode* newRightNode)
{
	this->rightNode = newRightNode;
}

SmartFeatureTreeNode * SmartFeatureTreeNode::getLeftNode()
{
	return this->leftNode;
}

SmartFeatureTreeNode * SmartFeatureTreeNode::getRightNode()
{
	return this->rightNode;
}

long SmartFeatureTreeNode::getGlobalNodeId()
{
	return this->globalNodeId;
}

long SmartFeatureTreeNode::getLocalNodeId()
{
	return this->localNodeId;
}

long SmartFeatureTreeNode::getLocalParentNodeId()
{
	return this->localParentNodeId;
}
