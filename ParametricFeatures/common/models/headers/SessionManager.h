#pragma once

#include "../../utils/headers/StringUtils.hpp"

using namespace std;

class SessionManager {

private:
	static SessionManager* _instance;
	string _dataOutputFilePath;
	string _ifcOutputFilePath;
	string _outputFolderPath;
	string _dgnFileName;
	string _currentDayLogsFolderPath;
	
	// Private constructor so that no objects can be created.
	SessionManager();
public:
	static SessionManager *getInstance() {
		if (!_instance) {
			_instance = new SessionManager();
		}
			
		return _instance;
	}
	
	string getDataOutputFilePath();
	void setDataOutputFilePath(string dataOutputFilePath);


	string getIfcOutputFilePath();
	void setIfcOutputFilePath(string ifcOutputFilePath);

	string getOutputFolderPath();
	void setOutputFolderPath(string outputFolderPath);

	string getDgnFileName();
	void setDgnFileName(string path);

	string getCurrentDayLogsFolderPath();
	void setCurrentDayLogsFolderPath(string logsFolderPath);

};