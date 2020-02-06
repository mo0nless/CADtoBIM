#pragma once

#include "PropertiesReader.h"

class GraphicsProcessor : public IElementGraphicsProcessor
{
public:
	GraphicsProcessor(std::ofstream &mOutfile, std::string& mFilePath);
	void setPropertiesDictionary(PropertiesDictionary* propsDict);
	void updateClassAndID(std::string elemClName, Int64 elemID);
private:
	inline void PrintPrincipalAreaMoments(ISolidPrimitiveCR& primitive);
	inline void GraphicsProcessor::PrintPrincipalProperties(DRange3d& range, DVec3d& rotation, DPoint4d& qRotation, Transform& localToWorld);

	virtual BentleyStatus _ProcessTextString(TextStringCR text) override;
	virtual BentleyStatus _ProcessCurvePrimitive(ICurvePrimitiveCR curve, bool isClosed, bool isFilled) override;
	virtual BentleyStatus _ProcessCurveVector(CurveVectorCR curves, bool isFilled) override;
	virtual bool _ProcessAsFacets(bool isPolyface) const override;
	virtual bool _ProcessAsBody(bool isCurved) const override;
	virtual BentleyStatus _ProcessSurface(MSBsplineSurfaceCR surface) override;
	virtual BentleyStatus _ProcessBody(ISolidKernelEntityCR entity, IFaceMaterialAttachmentsCP attachments) override;
	virtual BentleyStatus _ProcessFacets(PolyfaceQueryCR meshData, bool isFilled) override;
	virtual BentleyStatus _ProcessSolidPrimitive(ISolidPrimitiveCR primitive) override;

	WString myString;
	std::ofstream &outfile;
	std::string filePath;
	Int64 elementID;
	PropertiesDictionary* propsDictionary;
	std::string elemClassName;
};

