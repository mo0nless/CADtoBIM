#pragma once

#include "../../../logging/headers/Logger.h"


#include "../../graphic_properties/headers/GraphicsProcessor.h"
#include "../../../common/utils/headers/StringUtils.hpp"
#include "../../../common/models/headers/SessionManager.h"
#include "../../../modeler\data_writer\headers\ModelerDataWriterManager.h"

class InitializationHelper
{
public:
	InitializationHelper(vector<PersistentElementRefP> allGraphicElements);

	void processDgnGraphicsElements();

	vector<IfcElementBundle*>& getIfcElementBundleVector();

private:	
	Logs::Logger* _logger = Logs::Logger::getLogger();
	
	SmartFeatureContainer* createSmartFeatureContainer(ElementHandle currentElem, SmartFeatureNodePtr sFeatNode, ElementHandle leafNode, T_SmartFeatureVector sFeatVec);
	StatusInt iterateSubElements(ElementRefP elementRefP, IfcElementBundle*& ifcElementBundle);

	DgnModelP _dgnModel;

	ModelerDataWriterManager* _modelerDataWriterManager;
	PropertiesReaderProcessor* _propertiesReaderProcessor;

	PBAR::DialogCompletionBar* _progressBar;

	vector<PersistentElementRefP> _allGraphicElements;

	vector<IfcElementBundle*> _ifcElementBundleVector;
};
