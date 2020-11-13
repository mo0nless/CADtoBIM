// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently

#pragma once


//#define WIN32_LEAN_AND_MEAN		// Exclude rarely-used stuff from Windows headers
// Windows Header Files:
//#include <windows.h>

#define _USE_MATH_DEFINES

#include <cctype>
#include <algorithm>
#include <string>
#include <iostream>
#include <fstream> 
#include <filesystem>
#include <cmath>
#include <vector>
#include <map>
#include <tuple>
#include <regex>
#include <sstream>
//#include <thread>



#include <ifcparse\IfcSchema.h>
#include <ifcparse\Ifc2x3.h>
#include <ifcparse\Ifc4.h>
#include <ifcparse\Ifc4x1.h>
#include <ifcparse\utils.h>
#include <ifcparse\IfcHierarchyHelper.h>

#include "logging\headers\Logger.h"

//#include <../sqlite/sqlite3.h>

//#include <ifcgeom\kernels\opencascade\IfcRegister.h>

//#include <ifcgeom/kernels/opencascade/IfcGeom.h>


//#include <boost/any.hpp>

//#include <boost/thread.hpp>
//#include <boost/thread/mutex.hpp>

//#include "common\utils\headers\Mutex.h"
#include "common\utils\headers\ProgressBar.hpp"
#include "common\utils\headers\NotificationMessage.h"
//#include "boost\log\core.hpp"
//#include <boost/log/trivial.hpp>
//#include <boost/log/expressions.hpp>
//#include <boost/log/utility/setup/file.hpp>


//#include <msoutput.fdf>
#include <PSolid/PSolidCoreAPI.h>
#include <Bentley/WString.h>

#include <Mstn/isessionmgr.h>
#include <Mstn/Smartfeature/SmartfeatureAPI.h>
#include <Mstn/MdlApi/MdlApi.h>
#include <Mstn/MdlApi/mspop.h>
#include <Mstn/PSolid/mssolid.h>
#include <Mstn/PSolid/mssolid.fdf>
#include <Mstn/cmdlist.r.h>


#include <DgnPlatform/DisplayHandler.h>
#include <DgnPlatform/ElementGraphics.h>
//#include <DgnPlatform/ElementGeometry.h>
#include <DgnPlatform/Tools/ConfigurationManager.h>
#include <DgnPlatform/DgnFileIO/ModelInfo.h>
#include <DgnPlatform/DgnFileIO/UnitDefinition.h>

#include <DgnPlatform/ElementHandle.h>
#include <DgnPlatform/DgnECInstance.h>
#include <DgnPlatform/DgnECManager.h>
#include <DgnPlatform/DgnPlatformLib.h>
#include <DgnPlatform/ExportMacros.h>
#include <DgnPlatform/CellHeaderHandler.h>

#include <DgnView/DgnElementSetTool.h>
#include <DgnView/LocateSubEntityTool.h>   
#include <DgnView/SelectionSetManager.h>   
#include <DgnPlatform/DgnPlatformApi.h>
#include <DgnPlatform\ViewContext.h>

#include <DgnPlatform\DetailingSymbol\DetailingSymbolCore.r.h>
#include <DgnPlatform\DetailingSymbol\Detailingsymbol.h>
#include <DgnPlatform\NamedView.h>

#include <Mstn/isessionmgr.h>
#include <Mstn/ElementPropertyUtils.h>
#include <Mstn\Constraint3dElement\Constraint3dElementApi.h>


//#include <ECObjects/ECSchema.h>
#include <ECObjects/ECObjects.h>
#include <ECObjects/ECObjectsAPI.h>
//#include <ECObjects/ECValue.h>
#include <Geom/SolidPrimitive.h>


#include <Mstn\MdlApi\MdlApi.h>
#include <Mstn\MdlApi\modelindex.fdf>
#include <Mstn\MdlApi\mscell.fdf>
#include <Mstn\cmdlist.r.h>


USING_NAMESPACE_BENTLEY_ECOBJECT;
USING_NAMESPACE_BENTLEY_DGNPLATFORM;
USING_NAMESPACE_BENTLEY;
USING_NAMESPACE_BENTLEY_MSTNPLATFORM;
USING_NAMESPACE_BENTLEY_MSTNPLATFORM_ELEMENT;
USING_NAMESPACE_SMARTFEATURE;



