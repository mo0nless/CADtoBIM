#pragma once

#include "../../headers/GraphicsProcessor.h"
#include "../../common/utils/headers/StringUtils.hpp"

class InitializationEnhancer
{
public:
	InitializationEnhancer();
	
	void processDgnGraphicsElements(std::vector<DictionaryProperties*>& propsDictVec, std::vector<SmartFeatureContainer*>& smartFeatureContainerVector);
private:	
	SmartFeatureContainer* createSmartFeatureContainer(ElementHandle currentElem, SmartFeatureNodePtr sFeatNode, ElementHandle leafNode, T_SmartFeatureVector sFeatVec);
	void testFunction(PersistentElementRefP elemRef);
	PersistentElementRefList* pGraElement;
	std::string filePath;
	DgnModelP mDgnModel;
	WString mDgnFileName;
};
