#pragma once

/**
 * @file SessionManager.h
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include "../../utils/headers/StringUtils.hpp"

using namespace std;
using namespace Common::Utilities;

namespace Common
{
	namespace Models
	{
		/**
		 * @brief Class that helps manatining infos oif the session while the application runs
		 * 
		 */
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
			/**
			 * @brief Get the Instance object
			 * 
			 * @return SessionManager* 
			 */
			static SessionManager *getInstance() {
				if (!_instance) {
					_instance = new SessionManager();
				}

				return _instance;
			}

			/**
			 * @brief Get the Data Output File Path object
			 * 
			 * @return string 
			 */
			string getDataOutputFilePath();

			/**
			 * @brief Set the Data Output File Path object
			 * 
			 * @param dataOutputFilePath 
			 */
			void setDataOutputFilePath(string dataOutputFilePath);

			/**
			 * @brief Get the Ifc Output File Path object
			 * 
			 * @return string 
			 */
			string getIfcOutputFilePath();

			/**
			 * @brief Set the Ifc Output File Path object
			 * 
			 * @param ifcOutputFilePath 
			 */
			void setIfcOutputFilePath(string ifcOutputFilePath);

			/**
			 * @brief Get the Output Folder Path object
			 * 
			 * @return string 
			 */
			string getOutputFolderPath();

			/**
			 * @brief Set the Output Folder Path object
			 * 
			 * @param outputFolderPath 
			 */
			void setOutputFolderPath(string outputFolderPath);

			/**
			 * @brief Get the Dgn File Name object
			 * 
			 * @return string 
			 */
			string getDgnFileName();

			/**
			 * @brief Set the Dgn File Name object
			 * 
			 * @param path 
			 */
			void setDgnFileName(string path);

			/**
			 * @brief Get the Current Day Logs Folder Path object
			 * 
			 * @return string 
			 */
			string getCurrentDayLogsFolderPath();

			/**
			 * @brief Set the Current Day Logs Folder Path object
			 * 
			 * @param logsFolderPath 
			 */
			void setCurrentDayLogsFolderPath(string logsFolderPath);
		};
	}
}