#include "../headers/ParametricFeatures.h"


#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4189)
StatusInt GetSmartFeatureTree(WCharCP unparsedP)
{
	vector<DictionaryProperties*> propsDictVec;
	vector<SmartFeatureContainer*> smartFeatureContainerVector;

	InitializationHelper* initializationHelper = new InitializationHelper();
	initializationHelper->processDgnGraphicsElements(propsDictVec, smartFeatureContainerVector);

	IfcBuilder* ifcBuilder = new IfcBuilder();
	ifcBuilder->buildIfc(propsDictVec, smartFeatureContainerVector);

	string outputFolderPath = SessionManager::getInstance()->getOutputFolderPath();

	char myDocPath[MAX_PATH];
	strcpy(myDocPath, outputFolderPath.c_str());

	ShellExecute(NULL, "open", myDocPath, NULL, NULL, SW_SHOW);
	

	return SUCCESS;
}
#pragma warning( pop ) 


/*=================================================================================**//**
* @description  Unload this application
* @param[in] unparsed Additional input supplied after command string.
+===============+===============+===============+===============+===============+======*/
void UnloadParametricFeatures(WCharCP unparsedP)
{
	auto taskID = mdlSystem_getCurrTaskID();
	mdlDialog_cmdNumberQueue(FALSE, CMD_MDL_UNLOAD, taskID, INPUTQ_HEAD); //INPUTQ_EOQ
	return;
}
