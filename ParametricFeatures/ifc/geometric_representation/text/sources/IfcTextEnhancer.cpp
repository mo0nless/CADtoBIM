#include "..\headers\IfcTextEnhancer.h"

IfcTextEnhancer::IfcTextEnhancer()
{
}

void IfcTextEnhancer::enhance(IfcHierarchyHelper<Ifc4>& file, TextGraphicProperties* textGraphicProperties, IfcElementBundle *& ifcElementBundle, IfcGraphicPropertiesBundle * ifcGraphicPropertiesBundle)
{
	{
		_logger->logDebug(__FILE__, __LINE__, __func__);

		if (textGraphicProperties != nullptr) {
			Ifc4::IfcGeometricRepresentationItem* ifcRepresentationItem = buildTextString(textGraphicProperties, file, ifcGraphicPropertiesBundle);
			if (ifcRepresentationItem != nullptr)
			{
				ifcGraphicPropertiesBundle->setIfcRepresentationItem(ifcRepresentationItem);
				ifcGraphicPropertiesBundle->setRepresentationTypeIdentifier("Text", "Annotation");
			}
			else {
				_logger->logWarning(__FILE__, __LINE__, __func__, "ifcRepresentationItem IS NULL");
			}
		}

	}
}

Ifc4::IfcTextLiteralWithExtent * IfcTextEnhancer::buildTextString(TextGraphicProperties * textGraphicProperties, IfcHierarchyHelper<Ifc4>& file, IfcGraphicPropertiesBundle * ifcGraphicPropertiesBundle)
{
	Ifc4::IfcPlanarExtent* planarExtent = new Ifc4::IfcPlanarExtent(
		NumberUtils::convertCurrentUnitToMeters(textGraphicProperties->getHeight()),
		NumberUtils::convertCurrentUnitToMeters(textGraphicProperties->getWidth())
	);

	DVec3d centroid;
	centroid.Init(textGraphicProperties->getOrigin());

	Ifc4::IfcAxis2Placement3D* placement = IfcOperationsHelper::buildIfcAxis2Placement3D(
		centroid,
		textGraphicProperties->getVectorAxisZ(),
		textGraphicProperties->getVectorAxisX()
	);

	IfcEntityList* stylesList = new IfcEntityList();

	Ifc4::IfcTextStyleForDefinedFont* textStyleForDefinedFont = new Ifc4::IfcTextStyleForDefinedFont(
		buildIfcColor(textGraphicProperties->getTextColor()),
		buildIfcColor(textGraphicProperties->getBackgroundColor())
	); 
	//stylesList->push(textStyleForDefinedFont);

	Ifc4::IfcTextStyleTextModel* textStyleTextModel = buildIfcTextStyleTextModel();
	//stylesList->push(textStyleTextModel);

	Ifc4::IfcTextStyleFontModel* textStyleFontModel = new Ifc4::IfcTextStyleFontModel(
		textGraphicProperties->getFontName(),
		buildFamilyFont(),
		boost::none,
		boost::none,
		boost::none,
		new Ifc4::IfcLengthMeasure(
			NumberUtils::convertCurrentUnitToMeters(textGraphicProperties->getFontSize())
		)
	);
	//stylesList->push(textStyleFontModel);

	Ifc4::IfcTextStyle* textStyle = new Ifc4::IfcTextStyle(
		boost::none,
		textStyleForDefinedFont,
		textStyleTextModel,
		textStyleFontModel,
		true
	);
	stylesList->push(textStyle);
	
	Ifc4::IfcTextLiteralWithExtent* textWithLiteral = new Ifc4::IfcTextLiteralWithExtent(
		textGraphicProperties->getTextString(), 
		placement, 
		Ifc4::IfcTextPath::IfcTextPath_LEFT,
		planarExtent,
		"bottom-left"
	);
	
	boost::shared_ptr<IfcEntityList> stylesListPtr(stylesList);

	Ifc4::IfcStyledItem* styledItem = new Ifc4::IfcStyledItem(textWithLiteral, stylesListPtr, string("Text Style")); //item //styles //bool

	file.addEntity(styledItem);

	return textWithLiteral;
}

Ifc4::IfcColourRgb * IfcTextEnhancer::buildIfcColor(UInt32 color)
{
	_logger->logDebug(__FILE__, __LINE__, __func__);

	int blue = (color >> 16) & 0xFF;
	int green = (color >> 8) & 0xFF;
	int red = color & 0xFF;


	return new Ifc4::IfcColourRgb(string("Color"), red / 255.0, green / 255.0, blue / 255.0);
}

Ifc4::IfcTextStyleTextModel* IfcTextEnhancer::buildIfcTextStyleTextModel()
{
	Ifc4::IfcTextStyleTextModel* textStyleTextModel = new Ifc4::IfcTextStyleTextModel(
		new Ifc4::IfcDescriptiveMeasure("normal"),
		string("justify"),
		string("none"), //underline //overline
		new Ifc4::IfcDescriptiveMeasure("normal"),
		new Ifc4::IfcDescriptiveMeasure("normal"),
		string("none"), //capitalize
		new Ifc4::IfcDescriptiveMeasure("normal")
	); //indent //align //letter spacing

	return textStyleTextModel;
}

vector<string> IfcTextEnhancer::buildFamilyFont()
{
	vector<string> familyFont;
	familyFont.push_back("sans-serif");
	familyFont.push_back("serif");
	familyFont.push_back("cursive");
	familyFont.push_back("fantasy");
	familyFont.push_back("monospace");
	
	return familyFont;
}

vector<string> IfcTextEnhancer::buildFontStyle()
{
	vector<string> styleFont;
	styleFont.push_back("normal");
	styleFont.push_back("italic");
	styleFont.push_back("oblique");

	return styleFont;
}