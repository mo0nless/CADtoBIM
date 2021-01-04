#pragma once

#include <boost/thread.hpp>
#include <boost/thread/mutex.hpp>

#include "../../../stdafx.h"
#include "../../../common/utils/headers/StringUtils.hpp"
#include "../../../common/utils/headers/SmartFeatureTypeEnumUtils.h"

#include "../../../ifc/main/headers/IfcGraphicPropertiesBundle.h"
#include "../../../modeler/properties/smart_feature/headers/SmartFeatureContainer.h"

#include "../../../common/enums/headers/ShapesTypeEnum.h"
#include "../../../common/utils/headers/PropertyTypeEnumUtils.h"
#include "../../../common/models/headers/SessionManager.h"


#include <regex>

/// @addtogroup ElementProperties
/// @beginGroup

/*=================================================================================**//**
* Class for collecting the non-graphical properties of an element.
* This class use the ECquery system for retreiving information from the Bentley manager
* and store them in a dictionary.
* @see PropertiesDictionary 
* @bsiclass
+===============+===============+===============+===============+===============+======*/
class PropertiesReaderProcessor
{
public:
	//! The public constructor available.
	//! @param[in] the current element
	//! @param[in] the reference of the PropertiesDictionary
	//! @param[in] the reference of the SmartFeatureContainer
	vector<ReaderPropertiesBundle*> processElementReaderProperties(ElementHandleCR currentElem, IfcGraphicPropertiesBundle* elementBundle = nullptr);

	static PropertiesReaderProcessor* getInstance() 
	{
		call_once(initInstanceFlag, &PropertiesReaderProcessor::initPropertiesReaderProcessor);		
		return _PropertiesReaderProcessor;
	};
	string getElementClassName();
private:
	PropertiesReaderProcessor();

	string mElemClassName;

	Logs::Logger* _logger = Logs::Logger::getLogger();		

	// Handles persistance of ECInstances
	DgnECManagerR ecMgr = DgnECManager::GetManager();
	
	static PropertiesReaderProcessor* _PropertiesReaderProcessor;
	static once_flag initInstanceFlag;
	static void initPropertiesReaderProcessor()
	{
		_PropertiesReaderProcessor = new PropertiesReaderProcessor();
	}

	void mapECPropertiesToReaderProperties(DgnElementECInstanceP dgnElementECInstanceP, ReaderPropertiesBundle *&ReaderPropertiesBundle);
};

/// @endGroup
