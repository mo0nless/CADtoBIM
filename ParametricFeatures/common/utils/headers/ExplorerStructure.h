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

namespace Common
{
	namespace Utilities
	{
		struct ExplorerStructure
		{
		public:
			static string mainFolderPath;
			static string mainFileName;

			static ExplorerStructure* getInstance()
			{
				call_once(initInstanceFlag, &ExplorerStructure::initStructureExp);
				return _StructureExp;
			};

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

			static void createDefaultFilesStructure()
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

				string documentsPath(my_documents);

				mainFolderPath = documentsPath + "\\IfcModels";
				// create main folder
				createFolder(mainFolderPath);

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

				updateFileNameFilePath();

			}

			static void updateFileNameFilePath()
			{
				string fNamePath = StringUtils::getNormalizedString(ISessionMgr::GetActiveDgnFile()->GetFileName());

				// get dgn file name
				char drive[_MAX_DRIVE];
				char dir[_MAX_DIR];
				char fname[_MAX_FNAME];
				char ext[_MAX_EXT];

				_splitpath_s(fNamePath.c_str(), drive, _MAX_DRIVE, dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT);

				string strName(fname);
				mainFileName = StringUtils::getNormalizedString(strName);

				SessionManager::getInstance()->setDgnFileName(mainFileName);
				SessionManager::getInstance()->setOutputFolderPath(mainFolderPath);

				string ifcOutputFileName = mainFolderPath + "\\" + fname + ".ifc";

				SessionManager::getInstance()->setIfcOutputFilePath(ifcOutputFileName);
			}

			static string BrowseFolder(string saved_path)
			{
				TCHAR path[MAX_PATH];

				const char * path_param = saved_path.c_str();

				BROWSEINFO bi = { 0 };
				bi.lpszTitle = ("Select where to save the IFC file:");
				bi.ulFlags = BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE;
				bi.lParam = reinterpret_cast<LPARAM>(path_param);//(LPARAM)path_param;
				bi.lpfn = BrowseFolderCallback;

				LPITEMIDLIST pidl = SHBrowseForFolder(&bi);

				if (pidl != 0)
				{
					//get the name of the folder and put it in path
					SHGetPathFromIDList(pidl, path);

					//free memory used
					IMalloc * imalloc = 0;
					if (SUCCEEDED(SHGetMalloc(&imalloc)))
					{
						imalloc->Free(pidl);
						imalloc->Release();
					}

					return path;
				}

				return saved_path;
			}

		private:
			ExplorerStructure() {};

			static ExplorerStructure* _StructureExp;
			static once_flag initInstanceFlag;
			static void initStructureExp()
			{
				_StructureExp = new ExplorerStructure();
			}

			static int CALLBACK BrowseFolderCallback(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
			{

				if (uMsg == BFFM_INITIALIZED)
				{
					/*string tmp = (const char *)lpData;
					std::cout << "path: " << tmp << std::endl;
					SendMessage(hwnd, BFFM_SETSELECTION, TRUE, lpData);*/

					LPCTSTR path = reinterpret_cast<LPCTSTR>(lpData);
					::SendMessage(hwnd, BFFM_SETSELECTION, true, (LPARAM)path);
				}

				return 0;
			}
		};

		string ExplorerStructure::mainFolderPath = "";
		string ExplorerStructure::mainFileName = "";

		once_flag ExplorerStructure::initInstanceFlag;
		ExplorerStructure* ExplorerStructure::_StructureExp = 0;
	}
}