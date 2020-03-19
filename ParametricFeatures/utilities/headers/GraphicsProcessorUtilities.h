#pragma once

#include "../../headers/PropertiesReaderProcessor.h"

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

	void setPropertiesDictionary(DictionaryProperties& newDictionaryProperties);
	void updateClassAndID(std::string elemClName, Int64 elemID);

	//std::ofstream* outfile;
	std::string filePath;
	Int64 elementID;
	std::string elemClassName;
	DictionaryProperties dictionaryProperties;
	
private:
	

};
