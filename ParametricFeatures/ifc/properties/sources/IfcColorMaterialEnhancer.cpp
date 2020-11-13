#include "../headers/IfcColorMaterialEnhancer.h"

void IfcColorMaterialEnhancer::enhance(vector<IfcElementBundle*>& ifcBundleVector, IfcHierarchyHelper<Ifc4>& file, Ifc4::IfcOwnerHistory* ownerHistory)
{
	_logger->logInfo(__FILE__, __LINE__, __func__, "!- Starting enhancing the IFC color and material -!");

	this->_ownerHistory = ownerHistory;

	for (auto elemntBundle : ifcBundleVector) {
		for (auto graphicEl : elemntBundle->getIfcGraphicPropertiesBundleVector()) {
			processColour(*graphicEl,file);
		}
	}
	_logger->logInfo(__FILE__, __LINE__, __func__, "!- Ended enhancing the IFC color and material -!");

}

void IfcColorMaterialEnhancer::processColour(IfcGraphicPropertiesBundle& ifcGraphicPropertiesBundle, IfcHierarchyHelper<Ifc4>& file)
{
	_logger->logDebug(__FILE__, __LINE__, __func__);

	typedef Ifc4::IfcGloballyUniqueId guid;

	Ifc4::IfcColourRgb* ifcColour = buildIfcColor(ifcGraphicPropertiesBundle.getColor());

	IfcEntityList* ifcSurfaceStyleList = new IfcEntityList();


	//TODO check why curve is not colored
	if (dynamic_cast<Ifc4::IfcCurve*>(ifcGraphicPropertiesBundle.getIfcRepresentationItem()) != nullptr) {


		//Ifc4::IfcCurveStyleFontPattern* csfp = new Ifc4::IfcCurveStyleFontPattern(1, 0);
		//IfcTemplatedEntityList<Ifc4::IfcCurveStyleFontPattern>* entityListCurve = new IfcTemplatedEntityList<Ifc4::IfcCurveStyleFontPattern>();
		//entityListCurve->push(csfp);
		//boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcCurveStyleFontPattern>> ceva_cacat(entityListCurve);

		//Ifc4::IfcCurveStyleFont* ss = new Ifc4::IfcCurveStyleFont(string("font"), ceva_cacat);
		Ifc4::IfcPreDefinedCurveFont* pdcf = new Ifc4::IfcPreDefinedCurveFont("predefinedFont");
		//Ifc4::IfcRatioMeasure * rm = new Ifc4::IfcRatioMeasure(5.0);
		Ifc4::IfcDescriptiveMeasure* dm = new Ifc4::IfcDescriptiveMeasure("descriptiveMeasure");

		Ifc4::IfcCurveStyle* curveStyle = new Ifc4::IfcCurveStyle(string("style"), dm, pdcf, ifcColour, true);
		
		ifcSurfaceStyleList->push(curveStyle);
		file.addEntity(curveStyle);
	}
	else {
		Ifc4::IfcSurfaceStyleRendering* ifcSurfaceStyleRendering = new Ifc4::IfcSurfaceStyleRendering(
			ifcColour,
			ifcGraphicPropertiesBundle.getTransparency(), 
			new Ifc4::IfcNormalisedRatioMeasure(1),
			new Ifc4::IfcNormalisedRatioMeasure(1), 
			new Ifc4::IfcNormalisedRatioMeasure(1), 
			new Ifc4::IfcNormalisedRatioMeasure(1),
			new Ifc4::IfcNormalisedRatioMeasure(1), 
			new Ifc4::IfcNormalisedRatioMeasure(1), 
			Ifc4::IfcReflectanceMethodEnum::IfcReflectanceMethod_BLINN
		);

		file.addEntity(ifcSurfaceStyleRendering);

		IfcEntityList* entityList3 = new IfcEntityList();
		entityList3->push(ifcSurfaceStyleRendering);
		boost::shared_ptr<IfcEntityList> unitEntity3(entityList3);

		Ifc4::IfcSurfaceStyle* ifcSurfaceStyle = new Ifc4::IfcSurfaceStyle(string("ColourSurfaceStyle"), Ifc4::IfcSurfaceSide::IfcSurfaceSide_BOTH, unitEntity3);
		
		ifcSurfaceStyleList->push(ifcSurfaceStyle);
		file.addEntity(ifcSurfaceStyle);
	}

	boost::shared_ptr<IfcEntityList> ifcSurfaceStyleSharedList(ifcSurfaceStyleList);
	Ifc4::IfcPresentationStyleAssignment* ifcPresentationStyleAssignment = new Ifc4::IfcPresentationStyleAssignment(ifcSurfaceStyleSharedList);
	file.addEntity(ifcPresentationStyleAssignment);

	IfcEntityList* entityIfcPresentationStyleAssignmentList = new IfcEntityList();
	entityIfcPresentationStyleAssignmentList->push(ifcPresentationStyleAssignment);
	boost::shared_ptr<IfcEntityList> ifcPresentationStyleAssignmentList(entityIfcPresentationStyleAssignmentList);
	Ifc4::IfcRepresentationItem::list::ptr styledItemList(new Ifc4::IfcRepresentationItem::list());

	Ifc4::IfcStyledItem* ifcStyledItem = new Ifc4::IfcStyledItem(
		ifcGraphicPropertiesBundle.getIfcRepresentationItem(), 
		ifcPresentationStyleAssignmentList,
		boost::none
	);

	file.addEntity(ifcStyledItem);
	styledItemList->push(ifcStyledItem);

	Ifc4::IfcStyledRepresentation* ifcStyledRepresentation = new Ifc4::IfcStyledRepresentation(
		file.getSingle<Ifc4::IfcRepresentationContext>(), 
		//geometricContext,
		boost::none,
		boost::none, styledItemList
	);

	file.addEntity(ifcStyledRepresentation);


	IfcTemplatedEntityList<Ifc4::IfcRepresentation>* ceva1 = new IfcTemplatedEntityList<Ifc4::IfcRepresentation>();
	ceva1->push(ifcStyledRepresentation);
	boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcRepresentation>> unitEntity7(ceva1);

	Ifc4::IfcMaterial* ifcMaterial;
	if (!ifcGraphicPropertiesBundle.getMaterial().empty()) {
		ifcMaterial = new Ifc4::IfcMaterial(ifcGraphicPropertiesBundle.getMaterial(), boost::none, boost::none);
	}
	else {
		ifcMaterial = new Ifc4::IfcMaterial("UndefinedMaerial", boost::none, boost::none);
		_logger->logWarning(__FILE__, __LINE__, __func__, "Undefined material");

	}
	

	Ifc4::IfcMaterialDefinitionRepresentation* ifcMaterialDefinitionRepresentation = new Ifc4::IfcMaterialDefinitionRepresentation(
		boost::none, 
		boost::none,
		unitEntity7, 
		ifcMaterial
	);

	file.addEntity(ifcMaterialDefinitionRepresentation);

	IfcEntityList* entityList8 = new IfcEntityList();
	entityList8->push(ifcGraphicPropertiesBundle.getIfcRepresentationItem());
	boost::shared_ptr<IfcEntityList> unitEntity8(entityList8);

	Ifc4::IfcRelAssociatesMaterial* ifcRelAssociatesMaterial = new Ifc4::IfcRelAssociatesMaterial(
		guid::IfcGloballyUniqueId("ElementAssociatesMaterial"), 
		//file.getSingle<Ifc4::IfcOwnerHistory>(),
		this->_ownerHistory,
		boost::none, 
		boost::none, 
		unitEntity8, 
		ifcMaterial
	);

	file.addEntity(ifcRelAssociatesMaterial);
}

Ifc4::IfcColourRgb * IfcColorMaterialEnhancer::buildIfcColor(UInt32 color)
{
	_logger->logDebug(__FILE__, __LINE__, __func__);

	// another method to get the color
	//UInt32 color = elemDisplayParamsCP->GetLineColorTBGR();
	//mdlElement_getSymbology(&color, NULL, NULL, elementHandle.GetElementCP());

	//auto rez = ISessionMgr::GetActiveDgnFile()->GetColorMapP();

	//auto colorDefinition = rez->GetColor(color);
	//auto rgbColorDefinition = colorDefinition.m_rgb;

	int blue = (color >> 16) & 0xFF;
	int green = (color >> 8) & 0xFF;
	int red = color & 0xFF;


	return new Ifc4::IfcColourRgb(string("Color"), red / 255.0, green / 255.0, blue / 255.0);
}
