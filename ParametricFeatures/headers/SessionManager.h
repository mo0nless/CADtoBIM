#pragma once

#include<string>

using namespace std;

class SessionManager {

private:
	static SessionManager* _instance;
	string _dataOutputFilePath;
	string _ifcOutputFilePath;

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
};