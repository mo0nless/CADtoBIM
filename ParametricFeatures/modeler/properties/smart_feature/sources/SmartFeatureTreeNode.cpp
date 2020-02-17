#include "../headers/SmartFeatureTreeNode.h"

SmartFeatureTreeNode::SmartFeatureTreeNode()
{
	this->leftNode = nullptr;
	this->rightNode = nullptr;
	this->smartFeatureProperties = new SmartFeatureProperties();
}

void SmartFeatureTreeNode::setSmartFeatureProperties(SmartFeatureProperties * newSmartFeatureProperties)
{
	this->smartFeatureProperties = newSmartFeatureProperties;
}

SmartFeatureProperties * SmartFeatureTreeNode::getSmartFeatureProperties()
{
	return this->smartFeatureProperties;
}

void SmartFeatureTreeNode::setLeftNode(SmartFeatureTreeNode * newLeftNode)
{
	this->leftNode = newLeftNode;
}

void SmartFeatureTreeNode::setRightNode(SmartFeatureTreeNode * newRightNode)
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
