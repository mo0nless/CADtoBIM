#include "../headers/ParametricFeatures.h"


#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4189)
StatusInt GetSmartFeatureTree(WCharCP unparsedP)
{
	InitializationEnhancer* initializationEnhancer = new InitializationEnhancer();

	std::vector<DictionaryProperties*> propsDictVec;
	std::vector<SmartFeatureContainer*> smartFeatureContainerVector;

	initializationEnhancer->processDgnGraphicsElements(propsDictVec, smartFeatureContainerVector);

	IfcBuilder* ifcBuilder = new IfcBuilder();
	ifcBuilder->buildIfc(propsDictVec, smartFeatureContainerVector);
	

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
