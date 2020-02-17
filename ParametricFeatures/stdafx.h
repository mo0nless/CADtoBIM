// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#pragma once


//#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// Windows Header Files:
//#include <windows.h>

#define _USE_MATH_DEFINES


#include <string>
#include <iostream>
#include <fstream> 
#include <filesystem>
#include <cmath>
#include <vector>
#include <map>
#include <tuple>

#include <ifcparse\IfcSchema.h>
#include <ifcparse\Ifc2x3.h>
#include <ifcparse\Ifc4.h>
#include <ifcparse\Ifc4x1.h>
#include <ifcparse\utils.h>
#include <ifcparse\IfcHierarchyHelper.h>

#include <boost/any.hpp>

#include <PSolid/PSolidCoreAPI.h>
#include <Bentley/WString.h>

#include <Mstn/isessionmgr.h>
#include <Mstn/Smartfeature/SmartfeatureAPI.h>
#include <Mstn/MdlApi/MdlApi.h>
#include <Mstn/cmdlist.r.h>

#include <DgnPlatform/DisplayHandler.h>
#include <DgnPlatform/ElementGraphics.h>
#include <DgnPlatform/DisplayHandler.h>
#include <DgnPlatform/ElementHandle.h>
#include <DgnPlatform/DgnECInstance.h>
#include <DgnPlatform/DgnECManager.h>
#include <DgnPlatform/DgnPlatformLib.h>

#include <DgnView/DgnElementSetTool.h>
#include <DgnView/LocateSubEntityTool.h>   

//#include <ECObjects/ECSchema.h>
#include <ECObjects/ECObjects.h>
#include <ECObjects/ECObjectsAPI.h>
//#include <ECObjects/ECValue.h>
#include <Geom/SolidPrimitive.h>

USING_NAMESPACE_BENTLEY_ECOBJECT;
USING_NAMESPACE_BENTLEY_DGNPLATFORM;
USING_NAMESPACE_BENTLEY;
USING_NAMESPACE_BENTLEY_MSTNPLATFORM;
USING_NAMESPACE_BENTLEY_MSTNPLATFORM_ELEMENT;
USING_NAMESPACE_SMARTFEATURE;



