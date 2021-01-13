#pragma once

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
		 *  Utility class for string operations
		 */
		struct StringUtils {
			/**
			*  Convert WString to string
			*  @param wStringValue[in]
			*  @return std:string
			*/
			inline static string getString(WString wStringValue) {

				wstring ws(wStringValue.c_str());
				string stringValue(ws.begin(), ws.end());

				return stringValue;
			}

			/**
			*  Convert WString to string
			*  @param wStringValue[in]
			*  @return std:string
			*/
			inline static WString getWString(string stringValue) {

				wstring ws(stringValue.begin(), stringValue.end());
				WString wString(ws.c_str());

				return wString;
			}

			/**
			*  Normalize string, remove special characters, otherwise exception thrown in IfcParse
			*  @param stringValue[in]
			*  @return std:string
			*/
			inline static string getNormalizedString(string stringValue) {

				stringValue.resize(remove_if(stringValue.begin(),
					stringValue.end(), [](char x) {return !isalnum(x) && !isspace(x) && static_cast<unsigned char>(x) > 127; }) - stringValue.begin());

				return stringValue;
			}

			inline static string getNormalizedString(WString wStringValue) {

				return getNormalizedString(getString(wStringValue));
			}


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