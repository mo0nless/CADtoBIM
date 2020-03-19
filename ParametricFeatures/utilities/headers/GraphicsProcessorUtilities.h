#pragma once

#include "../../headers/PropertiesReaderProcessor.h"
#include "../../modeler/properties/primitives/graphic/headers/PrimitiveGraphicProperties.h"
#include "../../modeler/properties/curves/graphic/headers/CurveGraphicProperties.h"

class GraphicsProcessorUtilities
{
public:
	GraphicsProcessorUtilities();

	void setSlabGraphicProperties(DgnBoxDetail dgnBoxDetail);
	void setConeGraphicProperties(DgnConeDetail dgnConeDetail);
	void setSphereGraphicProperties();
	void setTorusGraphicProperties(DgnTorusPipeDetail dgnTorusPipeDetail, double sweepRadians);

	void CurveParser(CurveVectorCP curvesVector);
	void PrintPrincipalAreaMoments(ISolidPrimitiveCR& primitive);
	void PrintPrincipalProperties(DRange3d& range, DVec3d& rotation, DPoint4d& qRotation, Transform& localToWorld);

	void setDictionaryProperties(DictionaryProperties& newDictionaryProperties);
	DictionaryProperties* getDictionaryProperties();
		
private:
	std::string filePath;
	DictionaryProperties dictionaryProperties;

};
