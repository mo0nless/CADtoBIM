#pragma once

#include "../stdafx.h"
#include "../common/utils/headers/StringUtils.hpp"
#include "../modeler/properties/headers/DictionaryProperties.h"

#include "../mapper/properties/headers/ReaderPropertiesMapper.h"
#include "../modeler/properties/smart_feature/headers/SmartFeatureContainer.h"

#include "../common/utils/headers/PrimitiveTypeEnumUtils.h"
#include "../common/enums/headers/CurvesTypeEnum.h"

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
	PropertiesReaderProcessor(ElementHandleCR currentElem, DictionaryProperties& dictionaryProperties, SmartFeatureContainer& smartFeatureContainer);

	//! Get the class Name of the current element 
	//! @return the string that has the class Name of the element.
	std::string getElemClassName();
private:
	std::ofstream outfile;
	std::string filePath;

	std::string elemClassName;
	PropertiesReaderProcessor();
};

/// @endGroup
