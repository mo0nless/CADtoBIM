#include "../headers/SmartFeatureTreeNode.h"

SmartFeatureTreeNode::SmartFeatureTreeNode()
{
	this->leftNode = nullptr;
	this->rightNode = nullptr;
	this->generalProperties = new GeneralProperties();
	this->readerProperties = new ReaderProperties();
	this->graphicProperties = new GraphicProperties();
}

GeneralProperties * SmartFeatureTreeNode::getGeneralProperties()
{
	return this->generalProperties;
}

ReaderProperties * SmartFeatureTreeNode::getReaderProperties()
{
	return this->readerProperties;
}

GraphicProperties * SmartFeatureTreeNode::getGraphicProperties()
{
	return this->graphicProperties;
}

void SmartFeatureTreeNode::setGraphicProperties(GraphicProperties* newGraphicProperties)
{
	this->graphicProperties = newGraphicProperties;
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
