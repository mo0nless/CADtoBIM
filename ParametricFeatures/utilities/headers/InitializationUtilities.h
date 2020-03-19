#pragma once

#include "../../headers/GraphicsProcessor.h"
#include "../../common/utils/headers/StringUtils.hpp"
//#include "GraphicsProcessorUtilities.h"

class InitializationUtilities
{
public:
	InitializationUtilities();
	
	std::vector<DictionaryProperties*> orderDictionaryPropertyAndSmartFeature(std::vector<DictionaryProperties*>& propsDictVec, std::vector<SmartFeatureContainer*>& smartFeatureContainerVector);
	void processDgnGraphicsElements(std::vector<DictionaryProperties*>& propsDictVec, std::vector<SmartFeatureContainer*>& smartFeatureContainerVector);

private:	
	SmartFeatureContainer* createSmartFeatureContainer(ElementHandle currentElem, SmartFeatureNodePtr sFeatNode, ElementHandle leafNode, T_SmartFeatureVector sFeatVec);

	PersistentElementRefList* pGraElement;
	std::string filePath;
	DgnModelP dgnModel;
	WString dgnFileName;

};
