#include "../headers/IfcColorEnhancer.h"

void IfcColorEnhancer::enhanceColors(std::vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file)
{
	for (auto elemntBundle : ifcBundleVector) {
		for (auto graphicEl : elemntBundle->getIfcGraphicPropertiesBundleVector()) {
			processColour(*elemntBundle, *graphicEl,file);
		}
	}
}

void IfcColorEnhancer::processColour(IfcElementBundle& ifcElementBundle,IfcGraphicPropertiesBundle& ifcGraphicPropertiesBundle, IfcHierarchyHelper<Ifc4>& file)
{

	typedef Ifc4::IfcGloballyUniqueId guid;

	Ifc4::IfcColourRgb* ifcColour = buildIfcColor(ifcGraphicPropertiesBundle.getColor());

	IfcEntityList* ifcSurfaceStyleList = new IfcEntityList();


	//if (dynamic_cast<Ifc4::IfcCurve*>(ifcGraphicPropertiesBundle.getIfcRepresentationItem()) != nullptr) {


	//	//Ifc4::IfcCurveStyleFontPattern* csfp = new Ifc4::IfcCurveStyleFontPattern(1, 0);
	//	//IfcTemplatedEntityList<Ifc4::IfcCurveStyleFontPattern>* entityListCurve = new IfcTemplatedEntityList<Ifc4::IfcCurveStyleFontPattern>();
	//	//entityListCurve->push(csfp);
	//	//boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCurveStyleFontPattern>> ceva_cacat(entityListCurve);

	//	//Ifc4::IfcCurveStyleFont* ss = new Ifc4::IfcCurveStyleFont(std::string("font"), ceva_cacat);
	//	Ifc4::IfcPreDefinedCurveFont* pdcf = new Ifc4::IfcPreDefinedCurveFont("predefinedFont");
	//	//Ifc4::IfcRatioMeasure * rm = new Ifc4::IfcRatioMeasure(5.0);
	//	Ifc4::IfcDescriptiveMeasure* dm = new Ifc4::IfcDescriptiveMeasure("descriptiveMeasure");

	//	Ifc4::IfcCurveStyle* curveStyle = new Ifc4::IfcCurveStyle(std::string("style"), dm, pdcf, ifcColour, true);
	//	
	//	ifcSurfaceStyleList->push(curveStyle);
	//	file.addEntity(curveStyle);
	//}
	//else {
		Ifc4::IfcSurfaceStyleRendering* ifcSurfaceStyleRendering = new Ifc4::IfcSurfaceStyleRendering(ifcColour,
			ifcGraphicPropertiesBundle.getTransparency(), new Ifc4::IfcNormalisedRatioMeasure(1),
			new Ifc4::IfcNormalisedRatioMeasure(1), new Ifc4::IfcNormalisedRatioMeasure(1), new Ifc4::IfcNormalisedRatioMeasure(1),
			new Ifc4::IfcNormalisedRatioMeasure(1), new Ifc4::IfcNormalisedRatioMeasure(1), Ifc4::IfcReflectanceMethodEnum::IfcReflectanceMethod_BLINN);
		file.addEntity(ifcSurfaceStyleRendering);

		IfcEntityList* entityList3 = new IfcEntityList();
		entityList3->push(ifcSurfaceStyleRendering);
		boost::shared_ptr<IfcEntityList> unitEntity3(entityList3);

		Ifc4::IfcSurfaceStyle* ifcSurfaceStyle = new Ifc4::IfcSurfaceStyle(std::string("ColourSurfaceStyle"), Ifc4::IfcSurfaceSide::IfcSurfaceSide_BOTH, unitEntity3);
		
		ifcSurfaceStyleList->push(ifcSurfaceStyle);
		file.addEntity(ifcSurfaceStyle);
	//}

	boost::shared_ptr<IfcEntityList> ifcSurfaceStyleSharedList(ifcSurfaceStyleList);
	Ifc4::IfcPresentationStyleAssignment* ifcPresentationStyleAssignment = new Ifc4::IfcPresentationStyleAssignment(ifcSurfaceStyleSharedList);
	file.addEntity(ifcPresentationStyleAssignment);

	IfcEntityList* entityIfcPresentationStyleAssignmentList = new IfcEntityList();
	entityIfcPresentationStyleAssignmentList->push(ifcPresentationStyleAssignment);
	boost::shared_ptr<IfcEntityList> ifcPresentationStyleAssignmentList(entityIfcPresentationStyleAssignmentList);
	Ifc4::IfcRepresentationItem::list::ptr styledItemList(new Ifc4::IfcRepresentationItem::list());

	Ifc4::IfcStyledItem* ifcStyledItem = new Ifc4::IfcStyledItem(ifcGraphicPropertiesBundle.getIfcRepresentationItem(), ifcPresentationStyleAssignmentList,
		boost::none);
	file.addEntity(ifcStyledItem);
	styledItemList->push(ifcStyledItem);

	Ifc4::IfcStyledRepresentation* ifcStyledRepresentation = new Ifc4::IfcStyledRepresentation(file.getSingle<Ifc4::IfcRepresentationContext>(), boost::none,
		boost::none, styledItemList);
	file.addEntity(ifcStyledRepresentation);


	IfcTemplatedEntityList<Ifc4::IfcRepresentation>* ceva1 = new IfcTemplatedEntityList<Ifc4::IfcRepresentation>();
	ceva1->push(ifcStyledRepresentation);
	boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcRepresentation>> unitEntity7(ceva1);
	Ifc4::IfcMaterial* ifcMaterial = new Ifc4::IfcMaterial("Material", boost::none, boost::none);

	Ifc4::IfcMaterialDefinitionRepresentation* ifcMaterialDefinitionRepresentation = new Ifc4::IfcMaterialDefinitionRepresentation(boost::none, boost::none,
		unitEntity7, ifcMaterial);
	file.addEntity(ifcMaterialDefinitionRepresentation);

	IfcEntityList* entityList8 = new IfcEntityList();
	entityList8->push(ifcElementBundle.getIfcElement());
	boost::shared_ptr<IfcEntityList> unitEntity8(entityList8);
	Ifc4::IfcRelAssociatesMaterial* ifcRelAssociatesMaterial = new Ifc4::IfcRelAssociatesMaterial(guid::IfcGloballyUniqueId("ElementAssociatesMaterial"), file.getSingle<Ifc4::IfcOwnerHistory>(),
		boost::none, boost::none, unitEntity8, ifcMaterial);
	file.addEntity(ifcRelAssociatesMaterial);
}

Ifc4::IfcColourRgb * IfcColorEnhancer::buildIfcColor(UInt32 color)
{
	//UInt32 color = elemDisplayParamsCP->GetLineColorTBGR();
	//mdlElement_getSymbology(&color, NULL, NULL, elementHandle.GetElementCP());

	//auto rez = ISessionMgr::GetActiveDgnFile()->GetColorMapP();

	//auto colorDefinition = rez->GetColor(color);
	//auto rgbColorDefinition = colorDefinition.m_rgb;

	int blue = (color >> 16) & 0xFF;
	int green = (color >> 8) & 0xFF;
	int red = color & 0xFF;


	return new Ifc4::IfcColourRgb(std::string("Color"), red / 255.0, green / 255.0, blue / 255.0);
}