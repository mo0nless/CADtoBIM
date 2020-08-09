#pragma once

#include "../../headers/GraphicsProcessor.h"
#include "../../common/utils/headers/StringUtils.hpp"
#include "../../headers/GraphicElementTool.h"

class InitializationEnhancer
{
public:
	InitializationEnhancer();
	
	void processDgnGraphicsElements(std::vector<DictionaryProperties*>& propsDictVec, std::vector<SmartFeatureContainer*>& smartFeatureContainerVector);

private:	
	SmartFeatureContainer* createSmartFeatureContainer(ElementHandle currentElem, SmartFeatureNodePtr sFeatNode, ElementHandle leafNode, T_SmartFeatureVector sFeatVec);
	void testFunction(PersistentElementRefP elemRef);
	StatusInt findElementByType(ElementRefP elementRefP, DictionaryProperties* dictionaryProperties);
	//int ElementRefScanCallback(ElementRef eleR, void *callbackArg, ScanCriteriaP pCriteria);
	PersistentElementRefList* pGraElement;
	std::string filePath;
	DgnModelP mDgnModel;
	WString mDgnFileName;

};
