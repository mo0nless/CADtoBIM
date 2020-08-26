#include "../headers/SessionManager.h"

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
