#pragma once

#include "../stdafx.h"

#include "../headers/SmartFeatureProperties.h"

class SmartFeatureContainer 
{
private:
	UInt32 nodeId;
	std::string className;

	std::vector<SmartFeatureProperties> features;
	std::vector<UInt32> leafNodeIds;

public:
	SmartFeatureContainer(std::string nodeId, std::string className);

	UInt32 getNodeId();
	std::string getClassName();
	std::vector<SmartFeatureProperties> getFeatures();
	std::vector<UInt32> getLeafNodeIds();

};