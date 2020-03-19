#pragma once

#include "../../headers/GraphicsProcessor.h"
#include "../../common/utils/headers/StringUtils.hpp"
#include "GraphicsProcessorUtilities.h"

class InitializationUtilities
{
public:
	InitializationUtilities();

	SmartFeatureContainer* createSmartFeatureContainer(ElementHandle currentElem, SmartFeatureNodePtr sFeatNode, ElementHandle leafNode, T_SmartFeatureVector sFeatVec);
	std::vector<DictionaryProperties*> orderDictionaryPropertyAndSmartFeature(std::vector<DictionaryProperties*>& propsDictVec, std::vector<SmartFeatureContainer*>& smartFeatureContainerVector);
	void analyzeDgnGraphicsElements(std::vector<DictionaryProperties*>& propsDictVec, std::vector<SmartFeatureContainer*>& smartFeatureContainerVector);

private:	
	std::string filePath;
	DgnModelP dgnModel;
	WString dgnFileName;

	PersistentElementRefList* pGraElement;
};
