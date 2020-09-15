//--------------------------------------------------------------------------------------+
//
//    $Source: ParametricFeatures.cpp $
// 
//    $Copyright: (c) 2019 Bentley Systems, Incorporated. All rights reserved. $
//
//---------------------------------------------------------------------------------------+

//--------------------------------------------------------------------------------------
//    Include Files
//--------------------------------------------------------------------------------------

#include "../headers/ParametricFeatures.h"

//#include "../../../stdafx.h"


#if !defined (DIM)
#define DIM(a) ((sizeof(a)/sizeof((a)[0])))
#endif

//#include <iostream>
//#define LINEAR_TEMPLATE_NAME      L"CreatedGroup\\Created Linear Template"
//#define SHAPE_TEMPLATE_NAME       L"CreatedGroup\\Created Shape Template"
//#define HATCH_TEMPLATE_NAME       L"CreatedGroup\\Created Hatch Template"
//#define AREAPATTERN_TEMPLATE_NAME L"CreatedGroup\\Created AreaPattern Template"
//#define CELL_TEMPLATE_NAME        L"CreatedGroup\\Created Cell Template"
//#define TEXT_TEMPLATE_NAME        L"CreatedGroup\\Created Text Template"
//#define MLINE_TEMPLATE_NAME       L"CreatedGroup\\Created MLine Template"
//#define DIMENSION_TEMPLATE_NAME   L"CreatedGroup\\Created Dimension Template"
//#define HEADER_TEMPLATE_NAME      L"CreatedGroup\\Header"
//#define COMPONENT1_TEMPLATE_NAME  L"CreatedGroup\\Component1"
//#define COMPONENT2_TEMPLATE_NAME  L"CreatedGroup\\Component2"
//#include <iostream>
//#include <string>
//#include <fstream>
//#include <iostream>

//__declspec(dllexport) ElementID mdlElement_getID();
//#include <iostream>
//#include <fstream>
//#include <sstream>

Public RscFileHandle rfHandle; /* Resource file handle */

// Map key-in to function
static MdlCommandNumber    commandNumbers[] =
{
	{ (CmdHandler)UnloadParametricFeatures, CMD_PARAMETRICFEATURES_EXIT },
	{ (CmdHandler)GetSmartFeatureTree, CMD_TREE },
	0
};

void SetVersionNumber()
{
	VersionNumber version = { 10, 7, 6, 1 };
	mdlSystem_setMdlAppVersionNumber(mdlSystem_getCurrMdlDesc(), &version);
}

/*---------------------------------------------------------------------------------**//**
* @description  MdlMain
* @param        argc      The number of command line parameters sent to the application.
* @param        argv[]    The array of strings sent to the application on the command line.
* @bsimethod                                                              Bentley Systems
+---------------+---------------+---------------+---------------+---------------+------*/


extern "C" DLLEXPORT  void MdlMain(int argc, WCharCP argv[]) 
{
	//	Resources are defined in .r files
	mdlResource_openFile(&rfHandle, NULL, RSC_READONLY);	
	//	Register command numbers to enable you key in a command name to start a command
	mdlSystem_registerCommandNumbers(commandNumbers);
	//	Load the command table defined in ParametricFeatures.r
	mdlParse_loadCommandTable(NULL);

}
