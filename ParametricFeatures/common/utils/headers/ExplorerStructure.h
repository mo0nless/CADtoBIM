#pragma once

#include <windows.h>
#include <shellapi.h>
#include <string>
#include <iostream>
#include <shlobj.h>
#include <time.h>
#include <Mstn/isessionmgr.h>

#include "../../../common/models/headers/SessionManager.h"

USING_NAMESPACE_BENTLEY

struct ExplorerStructure
{
	static void createFolder(string folderPath)
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

	static void createFilesStructure()
	{
		//string filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";
		string filePath = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/TEST.txt";

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

		string ifcOutputFileName = mainFolderPath + "\\" + fname + ".ifc";

		SessionManager::getInstance()->setIfcOutputFilePath(ifcOutputFileName);

	}
};