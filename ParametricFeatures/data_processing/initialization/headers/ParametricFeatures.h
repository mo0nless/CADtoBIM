//--------------------------------------------------------------------------------------+
//
//    $Source: ParametricFeatures.h $
//
//    $Copyright: (c) 2019 Bentley Systems, Incorporated. All rights reserved. $
//
//--------------------------------------------------------------------------------------+
#pragma once

/*
* REMEMBER THAT THE INCLUDES ORDER MATTER
*/

#include <windows.h>
#include <shellapi.h>

#include "../headers/InitializationHelper.h"
#include "../../../ifc/main/headers/IfcBuilder.h"


#define CMD_TREE 0x0100000000000000UI64
#define CMD_SHAPE 0x0200000000000000UI64
#define CMD_PARAMETRICFEATURES_EXIT 0x0300000000000000UI64


/*
* C++ Compiler Name Mangling. Not sure if it's Necessary
*/

/*=================================================================================**//**
* Default header used by the main application that defines the Initialization and Unload functions
* @bsiclass
+===============+===============+===============+===============+===============+======*/
extern "C" {
	//  Function declarations inoculated against C++ compiler
	//  name mangling
	void UnloadParametricFeatures(WCharCP unparsedP);
	StatusInt GetSmartFeatureTree(WCharCP unparsedP);
	
	bool createFilesStructure();
	bool createFolder(string folderPath);

	NotificationManager::MessageBoxValue createNotificationMessage(NotificationManager::MessageBoxType messageType,
		string message, NotificationManager::MessageBoxIconType messageBoxIconType);

	NotificationManager::MessageBoxValue createErrorNotificationMessage(string message);
}



