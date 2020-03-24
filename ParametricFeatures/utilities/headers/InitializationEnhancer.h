#pragma once

#include "../../headers/GraphicsProcessor.h"
#include "../../common/utils/headers/StringUtils.hpp"
//#include "GraphicsProcessorUtilities.h"

class InitializationEnhancer
{
public:
	InitializationEnhancer();
	
	std::vector<DictionaryProperties*> orderDictionaryPropertyAndSmartFeature(std::vector<DictionaryProperties*>& propsDictVec, std::vector<SmartFeatureContainer*>& smartFeatureContainerVector);
	void processDgnGraphicsElements(std::vector<DictionaryProperties*>& propsDictVec, std::vector<SmartFeatureContainer*>& smartFeatureContainerVector);

private:	
	SmartFeatureContainer* createSmartFeatureContainer(ElementHandle currentElem, SmartFeatureNodePtr sFeatNode, ElementHandle leafNode, T_SmartFeatureVector sFeatVec);

	PersistentElementRefList* pGraElement;
	std::string filePath;
	DgnModelP mDgnModel;
	WString mDgnFileName;

};