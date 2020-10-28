#pragma once

#include <windows.h>
#include <iostream>
#include <shlobj.h>
#include <time.h>

//#include "../../../common/utils/headers/ThreadPool.h"
#include "../../../logging/headers/Logger.h"


#include "../../graphic_properties/headers/GraphicsProcessor.h"
#include "../../../common/utils/headers/StringUtils.hpp"
#include "../../../common/models/headers/SessionManager.h"
#include "../../../modeler\data_writer\headers\ModelerDataWriterManager.h"

class InitializationHelper
{
public:
	InitializationHelper();

	void processDgnGraphicsElements(vector<DictionaryProperties*>& propsDictVec, vector<SmartFeatureContainer*>& smartFeatureContainerVector);

private:	
	Logs::Logger* _logger = Logs::Logger::getLogger();
	
	SmartFeatureContainer* createSmartFeatureContainer(ElementHandle currentElem, SmartFeatureNodePtr sFeatNode, ElementHandle leafNode, T_SmartFeatureVector sFeatVec);
	StatusInt iterateSubElements(ElementRefP elementRefP, DictionaryProperties*& dictionaryProperties);
	PersistentElementRefList* pGraElement;
	string filePath;
	DgnModelP mDgnModel;
	WString mDgnFileName;
	ModelerDataWriterManager* _modelerDataWriterManager;
	PropertiesReaderProcessor* _propertiesReaderProcessor;

	PBAR::DialogCompletionBar* _progressBar;
};
