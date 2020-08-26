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

#include "../../../stdafx.h"


#if !defined (DIM)
#define DIM(a) ((sizeof(a)/sizeof((a)[0])))
#endif

#include <iostream>
#define LINEAR_TEMPLATE_NAME      L"CreatedGroup\\Created Linear Template"
#define SHAPE_TEMPLATE_NAME       L"CreatedGroup\\Created Shape Template"
#define HATCH_TEMPLATE_NAME       L"CreatedGroup\\Created Hatch Template"
#define AREAPATTERN_TEMPLATE_NAME L"CreatedGroup\\Created AreaPattern Template"
#define CELL_TEMPLATE_NAME        L"CreatedGroup\\Created Cell Template"
#define TEXT_TEMPLATE_NAME        L"CreatedGroup\\Created Text Template"
#define MLINE_TEMPLATE_NAME       L"CreatedGroup\\Created MLine Template"
#define DIMENSION_TEMPLATE_NAME   L"CreatedGroup\\Created Dimension Template"
#define HEADER_TEMPLATE_NAME      L"CreatedGroup\\Header"
#define COMPONENT1_TEMPLATE_NAME  L"CreatedGroup\\Component1"
#define COMPONENT2_TEMPLATE_NAME  L"CreatedGroup\\Component2"
#include <iostream>
#include <string>
#include <fstream>
#include <iostream>

//__declspec(dllexport) ElementID mdlElement_getID();
#include <iostream>
#include <fstream>
#include <sstream>

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

//using namespace std;
//int ElementRefScanCallback(ElementRefP eleR, void *callbackArg, ScanCriteriaP);
//int ScanForLinearElements(DgnModelRefP modelRef);
//int elmFunc(MSElement *element, void *params, int operation, UInt32 offset, MSElementDescr *elemDscrP);
//void IterateNestedModels(DgnModelRefP dgnModelRef);
//string narrowWString(wstring w);
//typedef struct scancallback_
//{
//	string levelName;
//} ScanCallBackData;
//string narrowWString(wstring w)
//{
//	string s(w.begin(), w.end());
//	return s;
//}
//string levelName;

extern "C" DLLEXPORT  void MdlMain(int argc, WCharCP argv[]) 
{
	//	Resources are defined in .r files
	mdlResource_openFile(&rfHandle, NULL, RSC_READONLY);	
	//	Register command numbers to enable you key in a command name to start a command
	mdlSystem_registerCommandNumbers(commandNumbers);
	//	Load the command table defined in ParametricFeatures.r
	mdlParse_loadCommandTable(NULL);

	//std::ofstream outfile;
	//std::string filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
	//outfile.open(filePath);
	//outfile << "" << std::endl;
	//outfile.close();
	//

	//if (argc == 3) {
	//	std::wstring ws(argv[2]);
	//	std::string stringValue(ws.begin(), ws.end());
	//	levelName = stringValue;

	//	outfile.open(filePath, std::ios_base::app);
	//	outfile << " level name="<<levelName << std::endl;
	//	outfile.close();
	//}
	//else
	//{
	//	mdlDialog_cmdNumberQueue(FALSE, CMD_MDL_UNLOAD, mdlSystem_getCurrTaskID(), MSInputQueuePos::INPUTQ_EOQ);//Unload program
	//	//return SUCCESS;//end program
	//	outfile.open(filePath, std::ios_base::app);
	//	outfile << " empty level name=" << std::endl;
	//	outfile.close();
	//}
	//DgnModelRefP dgnModelRef = mdlModelRef_getActive();

	//IterateNestedModels(dgnModelRef);
	//ScanForLinearElements(dgnModelRef);
	//mdlDialog_cmdNumberQueue(FALSE, CMD_MDL_UNLOAD, mdlSystem_getCurrTaskID(), MSInputQueuePos::INPUTQ_EOQ);

}
//void IterateNestedModels(DgnModelRefP dgnModelRef)
//{
//	ModelRefIteratorP  iterator;
//	DgnModelRefP modelRef;
//	mdlModelRefIterator_create(&iterator, dgnModelRef, MRITERATE_PrimaryChildRefs, 0);
//	while (NULL != (modelRef = mdlModelRefIterator_getNext(iterator)))
//	{
//		ScanForLinearElements(modelRef);
//		IterateNestedModels(modelRef);//This is the iterator
//	}
//}
//
//int ScanForLinearElements(DgnModelRefP modelRef)
//{
//	UShort typeMask[7];
//	ScanCallBackData data;
//	data.levelName = levelName;//levelName is global here
//	ScanCriteriaP	criteria = mdlScanCriteria_create();
//	mdlScanCriteria_setModel(criteria, modelRef);
//	//	Tell the scanner to call our function for each element found
//	mdlScanCriteria_setReturnType(criteria, MSSCANCRIT_ITERATE_ELMREF, FALSE, TRUE);
//	mdlScanCriteria_setElemRefCallback(criteria, ElementRefScanCallback, &modelRef);
//	//	Tell the scanner we're interested only in certain types of element
//	//	See mselems.h for the TMSK0_ macros 
//	memset(typeMask, 0, sizeof(typeMask));
//	typeMask[0] = TMSK0_CELL_HEADER | TMSK0_LINE | TMSK0_LINE_STRING | TMSK0_GROUP_DATA | TMSK0_SHAPE | TMSK0_TEXT_NODE | TMSK0_DIG_SETDATA | TMSK0_DGNFIL_HEADER | TMSK0_LEV_SYM | TMSK0_CURVE | TMSK0_CMPLX_STRING  | TMSK0_CMPLX_SHAPE | TMSK0_ELLIPSE | TMSK0_ARC;
//	typeMask[1] = TMSK1_TEXT | TMSK1_SURFACE | TMSK1_SOLID | TMSK1_BSPLINE_POLE | TMSK1_POINT_STRING | TMSK1_CONE | TMSK1_BSPLINE_SURFACE | TMSK1_BSURF_BOUNDARY | TMSK1_BSPLINE_KNOT | TMSK1_BSPLINE_CURVE | TMSK1_BSPLINE_WEIGHT;
//	typeMask[2] = TMSK2_DIMENSION | TMSK2_SHAREDCELL_DEF | TMSK2_SHARED_CELL | TMSK2_MULTILINE | TMSK2_ATTRIBUTE | TMSK2_TYPE44 | TMSK2_DGNSTORE_HDR;
//	typeMask[4] = TMSK4_MICROSTATION_ELM;
//	typeMask[5] = TMSK5_RASTER_HDR | TMSK5_RASTER_COMP | TMSK5_RASTER_LINK | TMSK5_RASTER_REFCMPN | TMSK5_RASTER_HIERARCHY | TMSK5_RASTER_HIERARCHYCMPN | TMSK5_RASTER_FRAME | TMSK5_TABLE_ENTRY | TMSK5_TABLE;
//	typeMask[6] = TMSK6_VIEW_GROUP | TMSK6_VIEW | TMSK6_LEVEL_MASK | TMSK6_REFERENCE_ATTACH;
//	mdlScanCriteria_setElementTypeTest(criteria, typeMask, sizeof(typeMask));
//	mdlScanCriteria_setDrawnElements(criteria);
//	mdlScanCriteria_scan(criteria, NULL, NULL, NULL);
//	mdlScanCriteria_free(criteria);
//	return 0;
//}
//
//int ElementRefScanCallback(ElementRefP eleR, void *callbackArg, ScanCriteriaP pCriteria) {
//
//	//ScanCallBackData*	data = (ScanCallBackData*)callbackArg;
//	DgnModelRefP modelRef = mdlScanCriteria_getModel(pCriteria);
//	DgnModelRefP dgnModelRef = modelRef;
//
//
//	EditElementHandle eh(eleR, dgnModelRef);
//	MSElement* eleP = eh.GetElementP();
//	UInt32 filePos = elementRef_getFilePos(eleR);
//	ElementId eleId = eleId = mdlElement_getID(eleP);
//	UInt32 level;
//	mdlElement_getProperties(&level, NULL, NULL, NULL, NULL, NULL, NULL, NULL, eleP);
//	WChar* pLevelNameOut = new WChar[100];
//	mdlLevel_getName(pLevelNameOut, 100, dgnModelRef, level);
//	wstring eleLevelNamew(pLevelNameOut);
//	string eleLevelName = narrowWString(eleLevelNamew);
//	if (mdlElement_isComplexHeader(eleP))
//	{
//		MSElementDescr* elemDescrP;
//		void* params = dgnModelRef;
//		UInt32 worked = mdlElmdscr_getByElemRef(&elemDescrP, eleR, dgnModelRef, TRUE, &filePos);
//		int(*foo)(MSElement *, void *, int, UInt32, MSElementDescr *);
//
//		std::string filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
//		std::ofstream outfile;
//		outfile.open(filePath, std::ios_base::app);
//		outfile << " edit elem handle id "<< eh.GetElementId() << std::endl;
//		outfile.close();
//
//		foo = &elmFunc;
//		int op = worked = mdlElmdscr_operation(elemDescrP, (PFElemOperation)foo, params, ELMD_ALL_ONCE);
//		if (op == 3)
//		{
//			mdlSelect_addElement(filePos, dgnModelRef);
//		}
//	}
//	if (eleLevelName.find(levelName) != std::string::npos) {//If the string is contained in the level's name
//		mdlSelect_addElement(filePos, dgnModelRef);
//	}
//
//	return SUCCESS;
//}
//int elmFunc(MSElement *element, void *params, int operation, UInt32 offset, MSElementDescr *elemDscrP)
//{
//	DgnModelRefP dgnModelRef = (DgnModelRefP)params;
//	UInt32 filePos = mdlElmdscr_getFilePos(elemDscrP);
//
//	UInt32 level;
//	mdlElement_getProperties(&level, NULL, NULL, NULL, NULL, NULL, NULL, NULL, element);
//	WChar* pLevelNameOut = new WChar[100];
//	mdlLevel_getName(pLevelNameOut, 100, dgnModelRef, level);
//	wstring eleLevelNamew(pLevelNameOut);
//	string eleLevelName = narrowWString(eleLevelNamew);
//
//	std::string filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
//	std::ofstream outfile;
//	outfile.open(filePath, std::ios_base::app);
//	outfile << " ele level name " << eleLevelName << std::endl;
//	outfile << " filePos" << filePos << std::endl;
//	outfile.close();
//
//	if (eleLevelName.find(levelName) != std::string::npos) {//If the string is contained in the level's name
//		mdlSelect_addElement(filePos, dgnModelRef);
//		return 3;
//	}
//	return SUCCESS;
//}