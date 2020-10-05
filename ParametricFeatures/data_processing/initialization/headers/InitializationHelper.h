#pragma once

#include <windows.h>
#include <iostream>
#include <shlobj.h>
#include <time.h>

//#include "../../../common/utils/headers/ThreadPool.h"
#include "../../../logging/headers/Logger.h"


#include "../../graphic_properties/headers/GraphicsProcessor.h"
#include "../../../common/utils/headers/StringUtils.hpp"
#include "../../../common/models/headers/SessionManager.h"
#include "../../../modeler\data_writer\headers\ModelerDataWriterManager.h"

class Iteration
{
public:
	StatusInt iterateSubElements(ElementHandle eh, DictionaryProperties*& dictionaryProperties)
	{
		_logger->logDebug(__FILE__, __LINE__, __func__);

		//ElementHandle eh(elementRefP);	 //	Can also construct an ElemHandle from an MSElementDescr*

		int index = 0;

		for (ChildElemIter child(eh); child.IsValid(); child = child.ToNext())
		{
			ElementHandle childHandle(child.GetElementRef());
			iterateSubElements(childHandle, dictionaryProperties);// , propertiesReaderProcessor);
			++index;
		}
		if (index == 0) {

			ElementBundle* elementBundle = new ElementBundle();
			elementBundle->setElementHandle(eh);

			ReaderPropertiesBundle* readerPropertiesBundle = _propertiesReaderProcessor->processElementReaderProperties(eh, elementBundle);
			elementBundle->setReaderPropertiesBundle(*readerPropertiesBundle);

			GraphicsProcessor* graphicsProcessor = new GraphicsProcessor();
			GraphicsProcessorHelper* graphicsProcessorHelper = graphicsProcessor->getGraphicsProcessorHelper();

			graphicsProcessorHelper->setElementHandle(eh);
			graphicsProcessorHelper->setElementBundle(*elementBundle);
			graphicsProcessorHelper->setDictionaryProperties(*dictionaryProperties);

			ElementGraphicsOutput::Process(eh, *graphicsProcessor);

			dictionaryProperties->addElementBundle(elementBundle);

			return SUCCESS;
		}

		return SUCCESS;
	}

	Iteration() { _propertiesReaderProcessor = PropertiesReaderProcessor::getInstance(); };

private:
	PropertiesReaderProcessor* _propertiesReaderProcessor;
	Logs::Logger* _logger = Logs::Logger::getLogger();
};

class InitializationHelper
{
public:
	InitializationHelper();

	void processDgnGraphicsElements(vector<DictionaryProperties*>& propsDictVec, vector<SmartFeatureContainer*>& smartFeatureContainerVector);
	void threadFunction(vector<ElementHandle> vecElemen, vector<DictionaryProperties*>& propsDictVec, vector<SmartFeatureContainer*>& smartFeatureContainerVector);

private:	
	Logs::Logger* _logger = Logs::Logger::getLogger();
	
	SmartFeatureContainer* createSmartFeatureContainer(ElementHandle currentElem, SmartFeatureNodePtr sFeatNode, ElementHandle leafNode, T_SmartFeatureVector sFeatVec);
	StatusInt iterateSubElements(ElementRefP elementRefP, DictionaryProperties*& dictionaryProperties);
	PersistentElementRefList* pGraElement;
	string filePath;
	DgnModelP mDgnModel;
	WString mDgnFileName;
	ModelerDataWriterManager* _modelerDataWriterManager;
	PropertiesReaderProcessor* _propertiesReaderProcessor;

	PBAR::DialogCompletionBar* _progressBar;

	Iteration* _iteration = new Iteration();
	template<typename ValueType>
	vector<vector<ValueType>> splitVector(const vector<ValueType>& vec, size_t n);
	mutable boost::shared_mutex _mutex;
};

template<typename ValueType>
vector<vector<ValueType>> InitializationHelper::splitVector(const vector<ValueType>& vec, size_t n)
{
	vector<vector<ValueType>> outVec;

	size_t length = vec.size() / n;
	size_t remain = vec.size() % n;

	size_t begin = 0;
	size_t end = 0;

	for (size_t i = 0; i < min(n, vec.size()); ++i)
	{
		end += (remain > 0) ? (length + !!(remain--)) : length;

		outVec.push_back(vector<ValueType>(vec.begin() + begin, vec.begin() + end));

		begin = end;
	}

	return outVec;
}