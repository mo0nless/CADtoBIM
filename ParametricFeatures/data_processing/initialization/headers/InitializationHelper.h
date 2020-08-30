#pragma once

#include "../../graphic_properties/headers/GraphicsProcessor.h"
#include "../../../common/utils/headers/StringUtils.hpp"
#include "../../../common/models/headers/SessionManager.h"

class InitializationHelper
{
public:
	InitializationHelper();
	
	void processDgnGraphicsElements(vector<DictionaryProperties*>& propsDictVec, vector<SmartFeatureContainer*>& smartFeatureContainerVector);
private:	
	SmartFeatureContainer* createSmartFeatureContainer(ElementHandle currentElem, SmartFeatureNodePtr sFeatNode, ElementHandle leafNode, T_SmartFeatureVector sFeatVec);
	StatusInt iterateSubElements(ElementRefP elementRefP, DictionaryProperties* dictionaryProperties);
	PersistentElementRefList* pGraElement;
	string filePath;
	DgnModelP mDgnModel;
	WString mDgnFileName;
};
