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

