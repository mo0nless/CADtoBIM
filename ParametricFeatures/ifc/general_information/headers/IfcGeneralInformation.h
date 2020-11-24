#pragma once

#include <ctime>
//#include "../../main/headers/IfcBuilder.h"
#include "../../../stdafx.h"

class IfcGeneralInformation 
{
public:
	static IfcGeneralInformation* getInstance()
	{
		call_once(initInstanceFlag, &IfcGeneralInformation::initIfcGeneralInformation);
		return _IfcGeneralInformation;
	};

	void setActorName(string name);
	void setActorSurName(string sName);
	void setActorEmail(string mail);
	void setActorRole(Ifc4::IfcRoleEnum::Value role);

	void buildIfcGeneralInfo();
	
	string getActorName();
	string getActorSurName();
	string getActorEmail();

	bool setDefaultValues();
	IfcHierarchyHelper<Ifc4>& getIfcHierarchyHelper();
	Ifc4::IfcGeometricRepresentationContext* getGeometricContext();
	Ifc4::IfcOwnerHistory* getOwnerHistory();
	Ifc4::IfcObjectPlacement* getObjectPlacement();
private:
	IfcGeneralInformation();

	static IfcGeneralInformation* _IfcGeneralInformation;
	static once_flag initInstanceFlag;
	static void initIfcGeneralInformation()
	{
		_IfcGeneralInformation = new IfcGeneralInformation();
	}
	
	IfcTemplatedEntityList<Ifc4::IfcActorRole>* getDeveloperRole();
	IfcTemplatedEntityList<Ifc4::IfcActorRole>* getUserRole();
	IfcTemplatedEntityList<Ifc4::IfcRepresentationContext>* getRepresentationContext();
	IfcTemplatedEntityList<Ifc4::IfcAddress>* getAddress();
	Ifc4::IfcUnitAssignment* getUnitAssignment();

	WString _orgaization, _fullName;
	string _actorName;
	string _actorSurName;
	string _actorEmail;
	Ifc4::IfcRoleEnum::Value _actorRole = Ifc4::IfcRoleEnum::Value(0);
	Ifc4::IfcGeometricRepresentationContext* _geometricContext;
	Ifc4::IfcOwnerHistory* _ownerHistory;
	Ifc4::IfcObjectPlacement* _objectPlacement;

	Ifc4::IfcUnitAssignment* ifcUnitAssignment;
	Ifc4::IfcActorRole::list::ptr appListOfActor;
	Ifc4::IfcGeometricRepresentationContext* ifcGeometricRepresentationContext;
	IfcHierarchyHelper<Ifc4> _file = IfcHierarchyHelper<Ifc4>(IfcParse::schema_by_name("IFC4"));
};
