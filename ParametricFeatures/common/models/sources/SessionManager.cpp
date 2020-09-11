#include "../headers/SessionManager.h"

SessionManager *SessionManager::_instance = 0;


SessionManager::SessionManager()
{
	this->_dataOutputFilePath = "";
	this->_ifcOutputFilePath = "";
}

string SessionManager::getDataOutputFilePath()
{
	//return this->getInstance()->_dataOutputFilePath;
	return this->_dataOutputFilePath;
}

void SessionManager::setDataOutputFilePath(string dataOutputFilePath)
{
	//this->getInstance()->_dataOutputFilePath = dataOutputFilePath;
	this->_dataOutputFilePath = dataOutputFilePath;
}

string SessionManager::getIfcOutputFilePath()
{
	//return this->getInstance()->_ifcOutputFilePath;
	return this->_ifcOutputFilePath;
}

void SessionManager::setIfcOutputFilePath(string ifcOutputFilePath)
{
	//this->getInstance()->_ifcOutputFilePath = ifcOutputFilePath;
	this->_ifcOutputFilePath = ifcOutputFilePath;
}

string SessionManager::getOutputFolderPath()
{
	//return this->getInstance()->_outputFolderPath;
	return this->_outputFolderPath;
}

void SessionManager::setOutputFolderPath(string outputFolderPath)
{
	//this->getInstance()->_outputFolderPath = outputFolderPath;
	this->_outputFolderPath = outputFolderPath;
}

string SessionManager::getDgnFileName()
{
	return this->_dgnFileName;
}

void SessionManager::setDgnFileName(string path)
{
	// get dgn file name
	char drive[_MAX_DRIVE];
	char dir[_MAX_DIR];
	char fname[_MAX_FNAME];
	char ext[_MAX_EXT];

	_splitpath_s(path.c_str(), drive, _MAX_DRIVE, dir, _MAX_DIR, fname, _MAX_FNAME, ext, _MAX_EXT);

	string s = fname;

	_dgnFileName = StringUtils::getNormalizedString(s);
}

