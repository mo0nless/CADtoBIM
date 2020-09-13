#include "../headers/ParametricFeatures.h"


#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4189)
StatusInt GetSmartFeatureTree(WCharCP unparsedP)
{
	createFilesStructure();
	Logs::Logger::getLogger()->logInfo(__FILE__, __LINE__, __FUNCTION__, "!!-- Starting application --!!");
	//mdlInput_sendKeyin(L"MsgCenter ClearMessages", true, MSInputQueuePos::INPUTQ_EOQ, L"0");

	NotificationManager::SetDispatchEvents(true);

	WString stringOutMsg;	
	
	string fileName = StringUtils::getNormalizedString(ISessionMgr::GetActiveDgnFile()->GetFileName());
	SessionManager::getInstance()->setDgnFileName(fileName);
	fileName = SessionManager::getInstance()->getDgnFileName();
	WString fname = StringUtils::getWString(fileName);

	stringOutMsg.Sprintf(L"Export the active '%s.dgn' file to IFC?", fname);

	NotificationManager::MessageBoxValue resultUser = NotificationManager::OpenMessageBox(
		NotificationManager::MessageBoxType::MESSAGEBOX_TYPE_YesNo,
		stringOutMsg.c_str(),
		NotificationManager::MessageBoxIconType::MESSAGEBOX_ICON_Question
	);
	
	if (NotificationManager::MessageBoxValue::MESSAGEBOX_VALUE_Yes == resultUser)
	{
		stringOutMsg.clear();
		stringOutMsg.Sprintf(L"Start IFC Conversion");
		NotificationMessage::send(stringOutMsg, OutputMessagePriority::Debug);

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

		stringOutMsg.clear();
		stringOutMsg.Sprintf(L"End IFC Conversion");

		NotificationMessage::send(stringOutMsg, OutputMessagePriority::Debug);
		Logs::Logger::getLogger()->logInfo(__FILE__, __LINE__, __FUNCTION__, "!!-- Ended the application process --!!");
	}

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

void createFilesStructure()
{
	string filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
	//string filePath = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/TEST.txt";

	SessionManager::getInstance()->setDataOutputFilePath(filePath);


	CHAR my_documents[MAX_PATH];
	HRESULT result = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, my_documents);

	if (result != S_OK) {
		cout << "Error: " << result << "\n";
	}
	else {
		cout << "Path: " << my_documents << "\n";
	}

	string documentsPath = my_documents;

	string mainFolderPath = documentsPath + "\\IfcModels";
	// create main folder
	createFolder(mainFolderPath);

	SessionManager::getInstance()->setOutputFolderPath(mainFolderPath);

	string logFolderPath = mainFolderPath + "\\logs";
	// create logs folder
	createFolder(logFolderPath);

	// get date to create logs by day
	time_t theTime = time(NULL);
	struct tm *aTime = localtime(&theTime);

	int day = aTime->tm_mday;
	int month = aTime->tm_mon + 1;
	int year = aTime->tm_year + 1900;

	string currentDayLogFolderPath = logFolderPath + "\\" + to_string(day) + "-" + to_string(month) + "-" + to_string(year);
	// create log folder
	createFolder(currentDayLogFolderPath);
	SessionManager::getInstance()->setCurrentDayLogsFolderPath(currentDayLogFolderPath);


	string re = StringUtils::getNormalizedString(ISessionMgr::GetActiveDgnFile()->GetFileName());


	// get dgn file name
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	_splitpath_s(re.c_str(), drive, _MAX_DRIVE, dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT);


	//string ifcOutputFileName1 = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/ifc/IfcCustomName.ifc";
	string ifcOutputFileName = mainFolderPath + "\\" + fname + ".ifc";

	SessionManager::getInstance()->setIfcOutputFilePath(ifcOutputFileName);

}
void createFolder(string folderPath)
{

	// create main folder
	if (CreateDirectory(folderPath.c_str(), NULL) ||
		ERROR_ALREADY_EXISTS == GetLastError())
	{
		// do something. status/boolean
	}
	else
	{
		// Failed to create directory. return status/boolean and log
	}
}
