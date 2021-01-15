#pragma once

/**
 * @file StringUtils.hpp
 * @author Stefano Beccaletto (stefano.beccaletto@tractebel.engie.com)
 * @brief 
 * @version 0.1
 * @date 2021-01-15
 * 
 * @copyright Copyright (c) 2021
 * 
 */

#include <string>
#include <sstream>
#include <vector>
#include <Bentley/WString.h>

using namespace std;

namespace Common
{
	namespace Utilities
	{

		/**
		 *  @brief Utility class for string operations
		 */
		struct StringUtils {
			/**
			*  @brief Convert WString to string
			*  @param wStringValue[in]
			*  @return std:string
			*/
			inline static string getString(WString wStringValue) {

				wstring ws(wStringValue.c_str());
				string stringValue(ws.begin(), ws.end());

				return stringValue;
			}

			/**
			*  @brief Convert WString to string
			*  @param wStringValue[in]
			*  @return std:string
			*/
			inline static WString getWString(string stringValue) {

				wstring ws(stringValue.begin(), stringValue.end());
				WString wString(ws.c_str());

				return wString;
			}

			/**
			*  @brief Normalize string, remove special characters, otherwise exception thrown in IfcParse
			*  @param stringValue[in]
			*  @return std:string
			*/
			inline static string getNormalizedString(string stringValue) {

				stringValue.resize(remove_if(stringValue.begin(),
					stringValue.end(), [](char x) {return !isalnum(x) && !isspace(x) && static_cast<unsigned char>(x) > 127; }) - stringValue.begin());

				return stringValue;
			}

			/**
			*  @brief Normalize WString, remove special characters, otherwise exception thrown in IfcParse
			*  @param stringValue[in]
			*  @return std:string
			*/
			inline static string getNormalizedString(WString wStringValue) {

				return getNormalizedString(getString(wStringValue));
			}

			/**
			 * @brief Get the Ifc Class Name 
			 * 
			 * @param ifcClassName 
			 * @return string 
			 */
			inline static string getIfcClassName(string ifcClassName) {

				vector<string> results;

				stringstream ss(ifcClassName);
				string str;
				while (getline(ss, str, ':')) {
					results.push_back(str);
				}

				if (results.size() == 0) {
					return  string();
				}

				return results[results.size() - 1];
			}
		};

	}
}