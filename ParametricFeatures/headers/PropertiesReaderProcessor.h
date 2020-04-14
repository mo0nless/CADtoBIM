#pragma once

#include "../stdafx.h"
#include "../common/utils/headers/StringUtils.hpp"
#include "../common/utils/headers/SmartFeatureTypeEnumUtils.h"

#include "../modeler/properties/headers/DictionaryProperties.h"

#include "../mapper/properties/headers/ReaderPropertiesMapper.h"
#include "../modeler/properties/smart_feature/headers/SmartFeatureContainer.h"

#include "../common/utils/headers/PrimitiveTypeEnumUtils.h"
#include "../common/enums/headers/ShapesTypeEnum.h"

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
	PropertiesReaderProcessor();

	//! The public constructor available.
	//! @param[in] the current element
	//! @param[in] the reference of the PropertiesDictionary
	//! @param[in] the reference of the SmartFeatureContainer
	void processElementReaderProperties(ElementHandleCR currentElem, DictionaryProperties& dictionaryProperties, SmartFeatureContainer& smartFeatureContainer);

private:
	std::string mElemClassName;
	
};

/// @endGroup
