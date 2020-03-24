#include "../headers/SmartFeatureTreeNode.h"

SmartFeatureTreeNode::SmartFeatureTreeNode()
{
	this->pLeftNode = nullptr;
	this->pRightNode = nullptr;
	this->pGeneralProperties = new GeneralProperties();
	this->pReaderProperties = new ReaderProperties();
	this->pGraphicProperties = new GraphicProperties();
}

GeneralProperties * SmartFeatureTreeNode::getGeneralProperties()
{
	return this->pGeneralProperties;
}

ReaderProperties * SmartFeatureTreeNode::getReaderProperties()
{
	return this->pReaderProperties;
}

GraphicProperties * SmartFeatureTreeNode::getGraphicProperties()
{
	return this->pGraphicProperties;
}

void SmartFeatureTreeNode::setGraphicProperties(GraphicProperties* newGraphicProperties)
{
	this->pGraphicProperties = newGraphicProperties;
}

void SmartFeatureTreeNode::setLeftNode(SmartFeatureTreeNode* newLeftNode)
{
	this->pLeftNode = newLeftNode;
}

void SmartFeatureTreeNode::setRightNode(SmartFeatureTreeNode* newRightNode)
{
	this->pRightNode = newRightNode;
}

SmartFeatureTreeNode * SmartFeatureTreeNode::getLeftNode()
{
	return this->pLeftNode;
}

SmartFeatureTreeNode * SmartFeatureTreeNode::getRightNode()
{
	return this->pRightNode;
}
