#pragma once

#include <fstream> 
#include <mutex>

#include "../../../common/models/headers/SessionManager.h"

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
#include <DgnPlatform/DgnFileIO/ModelInfo.h>
#include <DgnPlatform/DgnFileIO/UnitDefinition.h>

#include <DgnPlatform/DisplayHandler.h>
#include <DgnPlatform/ElementHandle.h>
#include <DgnPlatform/DgnECInstance.h>
#include <DgnPlatform/DgnECManager.h>
#include <DgnPlatform/DgnPlatformLib.h>
#include <DgnPlatform/ExportMacros.h>
#include <DgnPlatform/CellHeaderHandler.h>

#include <DgnView/DgnElementSetTool.h>
#include <DgnView/LocateSubEntityTool.h>   
#include <DgnPlatform/DgnPlatformApi.h>
#include <DgnPlatform\ViewContext.h>

#include <DgnPlatform\DetailingSymbol\DetailingSymbolCore.r.h>
#include <DgnPlatform\DetailingSymbol\Detailingsymbol.h>
#include <DgnPlatform\NamedView.h>

#include <Mstn/isessionmgr.h>
#include <Mstn/ElementPropertyUtils.h>
#include <Mstn\Constraint3dElement\Constraint3dElementApi.h>


#include <ECObjects/ECObjects.h>
#include <ECObjects/ECObjectsAPI.h>
#include <Geom/SolidPrimitive.h>

#include    <Mstn\MdlApi\MdlApi.h>
#include    <Mstn\MdlApi\modelindex.fdf>
#include    <Mstn\MdlApi\mscell.fdf>
#include    <Mstn\cmdlist.r.h>


USING_NAMESPACE_BENTLEY_ECOBJECT;
USING_NAMESPACE_BENTLEY_DGNPLATFORM;
USING_NAMESPACE_BENTLEY;
USING_NAMESPACE_BENTLEY_MSTNPLATFORM;
USING_NAMESPACE_BENTLEY_MSTNPLATFORM_ELEMENT;
USING_NAMESPACE_SMARTFEATURE;

using namespace std;

class ModelerDataWriterManager{

private:
	string _dataOutputFilePath;
	ofstream _outFile;

	bool _printDataEnabled;
	
	static once_flag initInstanceFlag;
	static ModelerDataWriterManager* _ModelerDataWriterManager;
	static void initModelerDataWriterManager() {
		_ModelerDataWriterManager = new ModelerDataWriterManager(true);
	}
	ModelerDataWriterManager(bool printDataEnabled);
	
public:

	static ModelerDataWriterManager* getInstance() 
	{
		call_once(initInstanceFlag, &ModelerDataWriterManager::initModelerDataWriterManager);
		return _ModelerDataWriterManager;
	}

#pragma region Primitives
	void writeGeneralPropertiesToFile(DRange3d& range, DVec3d& vectorRotation, DPoint4d& qRotation, Transform& localToWorld);

	void writeBoxDataToFile(DgnBoxDetail boxDetails);

	void writeConeDataToFile(DgnConeDetail coneDetails);

	void writeExtrusionDataToFile(DgnExtrusionDetail extrusionDetails);

	void writeRotationalSweepDataToFile(DgnRotationalSweepDetail rotSweepDetails);

	void writeRuledSweepDataToFile(DgnRuledSweepDetail ruledSweepDetails);

	void writeSphereDataToFile(DgnSphereDetail sphereDetails);

	void writeTorusDataToFile(DgnTorusPipeDetail torusDetails);
#pragma endregion

#pragma region Shapes
	void writeShapeCurvesVectorDataToFile(CurveVectorCR curvesVector);

	void writeCurvePrimitiveDataToFile(ICurvePrimitivePtr curvePrimitive);	
#pragma endregion

#pragma region Surface & Solid
	void writeMSBsplineSurfaceDataToFile(MSBsplineSurfaceCR msBsplineSurface);

	void writeBodyDataToFile(ISolidKernelEntityCR entity);
#pragma endregion

#pragma region General Data
	void writeElementInfoDataToFile(long elementID, WString elDescr);

	void writeInitializationDataToFile(ModelInfoCP modelInfo);

	void writeTitleProcessDataToFile(string s);

	void writeSinglePointDataToFile(DPoint3d point, int index = -1);

	template <class Num> 
	void writeTupleDataToFile(string s, Num data);	
	
	template <class Triplet>
	void writeTripetXyzDataToFile(string s, Triplet data);

#pragma endregion

};

template <class Num>
void ModelerDataWriterManager::writeTupleDataToFile(string s, Num data)
{
	if (!this->_printDataEnabled) {
		return;
	}

	this->_outFile.open(this->_dataOutputFilePath, ios_base::app, sizeof(string));
	this->_outFile << s << " = " << data << endl;
	this->_outFile << endl;
	this->_outFile.close();
}

template<class Triplet>
inline void ModelerDataWriterManager::writeTripetXyzDataToFile(string s, Triplet data)
{
	if (!this->_printDataEnabled) {
		return;
	}

	this->_outFile.open(this->_dataOutputFilePath, ios_base::app, sizeof(string));
	this->_outFile << fixed;
	this->_outFile << s << " = [" << data.x << ", " << data.y << ", " << data.z << "]" << endl;
	this->_outFile << endl;
	this->_outFile.close();
}
