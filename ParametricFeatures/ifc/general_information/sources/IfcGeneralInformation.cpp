#include "../headers/IfcGeneralInformation.h"

once_flag IfcGeneralInformation::initInstanceFlag;
IfcGeneralInformation* IfcGeneralInformation::_IfcGeneralInformation = 0;

IfcGeneralInformation::IfcGeneralInformation()
{
	ConfigurationManager::GetVariable(_orgaization, L"CONNECTUSER_ORGANIZATION");
	ConfigurationManager::GetVariable(_fullName, L"CONNECTUSER_NAME");
	_actorEmail = StringUtils::getString(_fullName);

	size_t pSep = _fullName.find(L".");
	size_t atSep = _fullName.find(L"@");

	_actorName = StringUtils::getString(_fullName.substr(0, pSep));
	_actorSurName = StringUtils::getString(_fullName.substr(pSep + 1, atSep - pSep -1));

	_actorName[0] = toupper(_actorName[0]);
	_actorSurName[0] = toupper(_actorSurName[0]);
}

void IfcGeneralInformation::setActorName(string name)
{
	if (!name.empty())
		_actorName = name;
}

void IfcGeneralInformation::setActorSurName(string sName)
{
	if (!sName.empty())
		_actorSurName = sName;
}

void IfcGeneralInformation::setActorEmail(string mail)
{
	if (!mail.empty())
		_actorEmail = mail;
}

void IfcGeneralInformation::setActorRole(Ifc4::IfcRoleEnum::Value role)
{
	_actorRole = role;
}

string IfcGeneralInformation::getActorName()
{
	return _actorName;
}
string IfcGeneralInformation::getActorSurName()
{
	return _actorSurName;
}
string IfcGeneralInformation::getActorEmail()
{
	return _actorEmail;
}

IfcHierarchyHelper<Ifc4>& IfcGeneralInformation::getIfcHierarchyHelper()
{
	return _file;
}

IfcTemplatedEntityList<Ifc4::IfcActorRole>* IfcGeneralInformation::getDeveloperRole()
{
	Ifc4::IfcActorRole* developerRole = new Ifc4::IfcActorRole(
		Ifc4::IfcRoleEnum::IfcRole_ENGINEER,
		string("Software Developer"),
		string("Stefano Beccaletto")
	);

	IfcTemplatedEntityList<Ifc4::IfcActorRole>* developerList = new IfcTemplatedEntityList<Ifc4::IfcActorRole>();
	developerList->push(developerRole);

	return developerList;
}

IfcTemplatedEntityList<Ifc4::IfcActorRole>* IfcGeneralInformation::getUserRole()
{
	Ifc4::IfcActorRole* userDefinedRole = new Ifc4::IfcActorRole(
		_actorRole,
		boost::none,
		_actorEmail
	);

	IfcTemplatedEntityList<Ifc4::IfcActorRole>* userList = new IfcTemplatedEntityList<Ifc4::IfcActorRole>();
	userList->push(userDefinedRole);

	return userList;
}

Ifc4::IfcUnitAssignment* IfcGeneralInformation::getUnitAssignment()
{
	Ifc4::IfcSIUnit* ifcUnitLength = new Ifc4::IfcSIUnit(Ifc4::IfcUnitEnum::IfcUnit_LENGTHUNIT, boost::none, Ifc4::IfcSIUnitName::IfcSIUnitName_METRE);
	Ifc4::IfcSIUnit* ifcUnitAngle = new Ifc4::IfcSIUnit(Ifc4::IfcUnitEnum::IfcUnit_PLANEANGLEUNIT, boost::none, Ifc4::IfcSIUnitName::IfcSIUnitName_RADIAN);

	// TODO [MP] review unit assigment
	IfcEntityList* unitEntityList = new IfcEntityList();
	unitEntityList->push(ifcUnitLength);
	unitEntityList->push(ifcUnitAngle);
	boost::shared_ptr<IfcEntityList> unitEntity(unitEntityList);

	Ifc4::IfcUnitAssignment* unitAssigment = new Ifc4::IfcUnitAssignment(unitEntity);

	return unitAssigment;
}

IfcTemplatedEntityList<Ifc4::IfcRepresentationContext>* IfcGeneralInformation::getRepresentationContext()
{
	//NOTE The inherited attribute ContextType shall have one of the following recognized values: 'Sketch', 'Outline', 'Design', 'Detail', 'Model', 'Plan', 'NotDefined'.
	string representationIdentifier = "*";
	string representationContextType = "Model"; //This is related to the specification of the context

	Ifc4::IfcDirection* trueNorthDirection = new Ifc4::IfcDirection(vector<double>{ 0.0, 1.0}); //This describe a plane and is 2D

	Ifc4::IfcAxis2Placement3D* originAndAxisPlacement = new Ifc4::IfcAxis2Placement3D(
		_file.addTriplet<Ifc4::IfcCartesianPoint>(0, 0, 0),
		_file.addTriplet<Ifc4::IfcDirection>(0, 0, 1), // Z direction
		_file.addTriplet<Ifc4::IfcDirection>(1, 0, 0)
	);

	//http://standards.buildingsmart.org/MVD/RELEASE/IFC4/ADD2_TC1/RV1_2/HTML/schema/ifcrepresentationresource/lexical/ifcgeometricrepresentationcontext.htm
	_geometricContext = new Ifc4::IfcGeometricRepresentationContext(
		representationIdentifier,
		representationContextType,
		3,
		1.0E-03,
		originAndAxisPlacement,
		trueNorthDirection
	);

	IfcTemplatedEntityList<Ifc4::IfcRepresentationContext>* listContext = new IfcTemplatedEntityList<Ifc4::IfcRepresentationContext>();
	listContext->push(_geometricContext);

	return listContext;
}

IfcTemplatedEntityList<Ifc4::IfcAddress>* IfcGeneralInformation::getAddress()
{
	Ifc4::IfcAddress* address = new Ifc4::IfcAddress(
		Ifc4::IfcAddressTypeEnum::IfcAddressType_OFFICE,
		StringUtils::getString(_orgaization),
		boost::none
	);

	IfcTemplatedEntityList<Ifc4::IfcAddress>* listOfAddresses = new IfcTemplatedEntityList<Ifc4::IfcAddress>();
	listOfAddresses->push(address);

	return listOfAddresses;
}


Ifc4::IfcGeometricRepresentationContext* IfcGeneralInformation::getGeometricContext()
{
	return _geometricContext;
}

Ifc4::IfcOwnerHistory* IfcGeneralInformation::getOwnerHistory()
{
	return _ownerHistory;
}

void IfcGeneralInformation::buildIfcGeneralInfo()
{
	typedef Ifc4::IfcGloballyUniqueId guid;

	//Unit Assigment
	Ifc4::IfcUnitAssignment* unitAssigment = getUnitAssignment();

	//Representation Context
	IfcTemplatedEntityList<Ifc4::IfcRepresentationContext>* listContext = getRepresentationContext();
	boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcRepresentationContext>> representationContextList(listContext);
		
	//User List 
	IfcTemplatedEntityList<Ifc4::IfcActorRole>* listActor = getUserRole();
	boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcActorRole>> userRoleList(listActor);

	//Developer List
	IfcTemplatedEntityList<Ifc4::IfcActorRole>* listDev = getDeveloperRole();
	boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcActorRole>> developerList(listDev);

	//Addtress List
	IfcTemplatedEntityList<Ifc4::IfcAddress>* listOfAddresses = getAddress();
	boost::shared_ptr<IfcTemplatedEntityList<Ifc4::IfcAddress>> addressList(listOfAddresses);


	//User Related
	Ifc4::IfcPerson* person = new Ifc4::IfcPerson(
		string(Ifc4::IfcRoleEnum::ToString(_actorRole)), //ID
		_actorSurName, //Surname
		_actorName, //Name
		boost::none,
		boost::none,
		boost::none,
		userRoleList,
		boost::none
	);
		
	//Organization
	Ifc4::IfcOrganization* organization = new Ifc4::IfcOrganization(
		StringUtils::getString(_orgaization),
		StringUtils::getString(_orgaization),
		boost::none,
		developerList,
		addressList
	);

	Ifc4::IfcPersonAndOrganization* personAndOrganization = new Ifc4::IfcPersonAndOrganization(
		person,
		organization,
		userRoleList
	);

	Ifc4::IfcApplication* application = new Ifc4::IfcApplication(
		organization,
		string("1.0"),
		string("OpenPlant IFC Exporter"),
		string("OpenPlant-IFC-Exp")
	);

	// Current date/time based on current system
	time_t currentTimeNow = time(0);

	_ownerHistory = new Ifc4::IfcOwnerHistory(
		personAndOrganization,
		application,
		Ifc4::IfcStateEnum::IfcState_READWRITE,
		Ifc4::IfcChangeActionEnum::IfcChangeAction_NOCHANGE,
		currentTimeNow, //last mod
		personAndOrganization,
		application,
		currentTimeNow //creation date
	);

	Ifc4::IfcProject* project = new Ifc4::IfcProject(
		guid::IfcGloballyUniqueId(SessionManager::getInstance()->getDgnFileName()),
		_ownerHistory,
		SessionManager::getInstance()->getDgnFileName(),
		string("OpenPlant IFC Exporter"),
		boost::none,
		boost::none,
		boost::none,
		representationContextList,
		unitAssigment
	);

	_file.addEntity(project);
}