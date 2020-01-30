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

#include "IfcGenerator.h"
#include "../utils/TypesUtils.h"
#include "GraphicsProcessor.h"
#include "PropertiesReader.h"
#include "../stdafx.h"


#define CMD_TREE 0x0100000000000000UI64
#define CMD_SHAPE 0x0200000000000000UI64
#define CMD_PARAMETRICFEATURES_EXIT 0x0300000000000000UI64


/*
* C++ Compiler Name Mangling. Not sure if it's Necessary
*/
extern "C" {
	//  Function declarations inoculated against C++ compiler
	//  name mangling
	void UnloadParametricFeatures(WCharCP unparsedP);
	StatusInt GetSmartFeatureTree(WCharCP unparsedP);
}



