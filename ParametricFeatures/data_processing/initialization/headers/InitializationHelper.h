#pragma once

#include <windows.h>
#include <iostream>
#include <shlobj.h>
#include <time.h>

//#include "../../../common/utils/headers/ctpl.h"
#include "../../../logging/headers/Logger.h"


#include "../../graphic_properties/headers/GraphicsProcessor.h"
#include "../../../common/utils/headers/StringUtils.hpp"
#include "../../../common/models/headers/SessionManager.h"
#include "../../../modeler\data_writer\headers\ModelerDataWriterManager.h"

class InitializationHelper
{
public:
	InitializationHelper();
	
	void processDgnGraphicsElements(vector<DictionaryProperties*>& propsDictVec, vector<SmartFeatureContainer*>& smartFeatureContainerVector);


private:	
	void createFilesStructure();
	void createFolder(string folderPath);

	template<typename T>
	vector<vector<T>> splitVector(const std::vector<T>& vec, size_t n);

	void processSubElemVector(vector<PersistentElementRefP> vecGraphicElement, vector<DictionaryProperties*>& propsDictVec, vector<SmartFeatureContainer*>& smartFeatureContainerVector);

	SmartFeatureContainer* createSmartFeatureContainer(ElementHandle currentElem, SmartFeatureNodePtr sFeatNode, ElementHandle leafNode, T_SmartFeatureVector sFeatVec);
	StatusInt iterateSubElements(ElementRefP elementRefP, DictionaryProperties* dictionaryProperties);
	PersistentElementRefList* pGraElement;
	string filePath;
	DgnModelP mDgnModel;
	WString mDgnFileName;
	ModelerDataWriterManager* _modelerDataWriterManager;
	DialogCompletionBar _progressBar;
};

template<typename T>
vector<vector<T>> InitializationHelper::splitVector(const vector<T>& vec, size_t n)
{
	vector<vector<T>> outVec;

	size_t length = vec.size() / n;
	size_t remain = vec.size() % n;

	size_t begin = 0;
	size_t end = 0;

	for (size_t i = 0; i < min(n, vec.size()); ++i)
	{
		end += (remain > 0) ? (length + !!(remain--)) : length;

		outVec.push_back(vector<T>(vec.begin() + begin, vec.begin() + end));

		begin = end;
	}

	return outVec;
}