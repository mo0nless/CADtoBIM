#pragma once

#include "../../headers/IfcBuilder.h"

class IfcGeneralInformation {
	
private:
	Ifc4::IfcUnitAssignment* ifcUnitAssignment;
	Ifc4::IfcActorRole::list::ptr appListOfActor;
	Ifc4::IfcGeometricRepresentationContext* ifcGeometricRepresentationContext;
};