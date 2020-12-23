#pragma once

#include "../../../logging/headers/Logger.h"


#include "../../graphic_properties/headers/GraphicsProcessor.h"
#include "../../../common/utils/headers/StringUtils.hpp"
#include "../../../common/models/headers/SessionManager.h"
#include "../../../modeler\data_writer\headers\ModelerDataWriterManager.h"

class InitializationHelper
{
public:
	InitializationHelper(vector<PersistentElementRefP> pGraElement);

	void processDgnGraphicsElements();

	vector<IfcElementBundle*>& getIfcElementBundleVector();
	vector<SmartFeatureContainer*>& getSmartFeatureContainerVector();

private:	
	Logs::Logger* _logger = Logs::Logger::getLogger();
	
	SmartFeatureContainer* createSmartFeatureContainer(ElementHandle currentElem, SmartFeatureNodePtr sFeatNode, ElementHandle leafNode, T_SmartFeatureVector sFeatVec);
	StatusInt iterateSubElements(ElementRefP elementRefP, IfcElementBundle*& ifcElementBundle);

	DgnModelP mDgnModel;

	ModelerDataWriterManager* _modelerDataWriterManager;
	PropertiesReaderProcessor* _propertiesReaderProcessor;

	PBAR::DialogCompletionBar* _progressBar;

	vector<PersistentElementRefP> pGraElement;

	vector<IfcElementBundle*> _ifcElementBundleVector;
};
