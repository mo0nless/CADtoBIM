#include "../headers/SessionManager.h"

using namespace Common::Models;

SessionManager *SessionManager::_instance = 0;


SessionManager::SessionManager()
{
	this->_dataOutputFilePath = "";
	this->_ifcOutputFilePath = "";
}

string SessionManager::getDataOutputFilePath()
{
	return this->_dataOutputFilePath;
}

void SessionManager::setDataOutputFilePath(string dataOutputFilePath)
{
	this->_dataOutputFilePath = dataOutputFilePath;
}

string SessionManager::getIfcOutputFilePath()
{
	return this->_ifcOutputFilePath;
}

void SessionManager::setIfcOutputFilePath(string ifcOutputFilePath)
{
	this->_ifcOutputFilePath = ifcOutputFilePath;
}

string SessionManager::getOutputFolderPath()
{
	return this->_outputFolderPath;
}

void SessionManager::setOutputFolderPath(string outputFolderPath)
{
	this->_outputFolderPath = outputFolderPath;
}

string SessionManager::getDgnFileName()
{
	return this->_dgnFileName;
}

void SessionManager::setDgnFileName(string path)
{
	_dgnFileName = path;
}

string SessionManager::getCurrentDayLogsFolderPath()
{
	return this->_currentDayLogsFolderPath;
}

void SessionManager::setCurrentDayLogsFolderPath(string logsFolderPath)
{
	this->_currentDayLogsFolderPath = logsFolderPath;
}

