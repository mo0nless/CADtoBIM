#include "../headers/SmartFeatureTreeNode.h"

SmartFeatureTreeNode::SmartFeatureTreeNode()
{
	this->mLeftNode = nullptr;
	this->mRightNode = nullptr;
	this->mGeneralProperties = new GeneralProperties();
	this->mReaderProperties = new ReaderProperties();
	this->mGraphicProperties = new GraphicProperties();
}

GeneralProperties * SmartFeatureTreeNode::getGeneralProperties()
{
	return this->mGeneralProperties;
}

ReaderProperties * SmartFeatureTreeNode::getReaderProperties()
{
	return this->mReaderProperties;
}

GraphicProperties * SmartFeatureTreeNode::getGraphicProperties()
{
	return this->mGraphicProperties;
}

void SmartFeatureTreeNode::setGraphicProperties(GraphicProperties* newGraphicProperties)
{
	this->mGraphicProperties = newGraphicProperties;
}

void SmartFeatureTreeNode::setLeftNode(SmartFeatureTreeNode* newLeftNode)
{
	this->mLeftNode = newLeftNode;
}

void SmartFeatureTreeNode::setRightNode(SmartFeatureTreeNode* newRightNode)
{
	this->mRightNode = newRightNode;
}

SmartFeatureTreeNode * SmartFeatureTreeNode::getLeftNode()
{
	return this->mLeftNode;
}

SmartFeatureTreeNode * SmartFeatureTreeNode::getRightNode()
{
	return this->mRightNode;
}
