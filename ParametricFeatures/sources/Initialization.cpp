#include "../headers/ParametricFeatures.h"

#ifndef Private
#define Private
#endif


typedef std::string S;
boost::none_t const null = boost::none;
using boost::any_cast;

class CSGBool {
private:
	typedef enum {
		OP_ADD, OP_SUBTRACT, OP_INTERSECT, OP_TERMINAL
	} Op;
	typedef enum {
		PRIM_BOX, PRIM_CONE, PRIM_CYLINDER, PRIM_PYRAMID, PRIM_SPHERE
	} Prim;

	double x, y, z, zx, zy, zz, xx, xy, xz, a, b, c;
	const CSGBool *left, *right;

	Op op;
	Prim prim;

	CSGBool& operate(Op oP, const CSGBool& p) {
		left = new CSGBool(*this);
		right = new CSGBool(p);
		this->op = oP;
		return *this;
	}

	CSGBool(Prim p, double la, double lb = 0., double lc = 0.)
		: prim(p), op(OP_TERMINAL),
		x(0.), y(0.), z(0.),
		zx(0.), zy(0.), zz(1.),
		xx(1.), xy(0.), xz(0.),
		a(la), b(lb), c(lc) {}
public:
	static CSGBool Sphere(double r) {
		return CSGBool(PRIM_SPHERE, r);
	}
	static CSGBool Box(double dx, double dy, double dz) {
		return CSGBool(PRIM_BOX, dx, dy, dz);
	}
	static CSGBool Pyramid(double dx, double dy, double dz) {
		return CSGBool(PRIM_PYRAMID, dx, dy, dz);
	}
	static CSGBool Cylinder(double r, double h) {
		return CSGBool(PRIM_CYLINDER, r, h);
	}
	static CSGBool Cone(double r, double h) {
		return CSGBool(PRIM_CONE, r, h);
	}

	CSGBool& move(
		double px = 0., double py = 0., double pz = 0.,
		double zX = 0., double zY = 0., double zZ = 1.,
		double xX = 1., double xY = 0., double xZ = 0.)
	{
		this->x = px; this->y = py;	this->z = pz;
		this->zx = zX; this->zy = zY; this->zz = zZ;
		this->xx = xX; this->xy = xY; this->xz = xZ;
		return *this;
	}

	CSGBool& add(const CSGBool& p) {
		return operate(OP_ADD, p);
	}
	CSGBool& subtract(const CSGBool& p) {
		return operate(OP_SUBTRACT, p);
	}
	CSGBool& intersect(const CSGBool& p) {
		return operate(OP_INTERSECT, p);
	}

	Ifc4::IfcRepresentationItem* serialize(IfcHierarchyHelper<Ifc4>& file) const {
		Ifc4::IfcRepresentationItem* my = nullptr;
		if (op == OP_TERMINAL) {
			Ifc4::IfcAxis2Placement3D* place = file.addPlacement3d(x, y, z, zx, zy, zz, xx, xy, xz);
			if (prim == PRIM_SPHERE) {
				my = new Ifc4::IfcSphere(place, a);
			}
			else if (prim == PRIM_BOX) {
				my = new Ifc4::IfcBlock(place, a, b, c);
			}
			else if (prim == PRIM_PYRAMID) {
				my = new Ifc4::IfcRectangularPyramid(place, a, b, c);
			}
			else if (prim == PRIM_CYLINDER) {
				my = new Ifc4::IfcRightCircularCylinder(place, b, a);
			}
			else if (prim == PRIM_CONE) {
				my = new Ifc4::IfcRightCircularCone(place, b, a);
			}
		}
		else {
			Ifc4::IfcBooleanOperator::Value o;
			if (op == OP_ADD) {
				o = Ifc4::IfcBooleanOperator::IfcBooleanOperator_UNION;
			}
			else if (op == OP_SUBTRACT) {
				o = Ifc4::IfcBooleanOperator::IfcBooleanOperator_DIFFERENCE;
			}
			else if (op == OP_INTERSECT) {
				o = Ifc4::IfcBooleanOperator::IfcBooleanOperator_INTERSECTION;
			}
			my = new Ifc4::IfcBooleanResult(o, left->serialize(file), right->serialize(file));
		}
		file.addEntity(my);
		return my;
	}
};

void test()
{
	typedef IfcParse::IfcGlobalId guid;
	/*const char filename[] = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/ifc/IfcCsgPrimitive.ifc";*/
	const char filename[] = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/ifc/IfcCsgPrimitive.ifc";
	
	IfcHierarchyHelper<Ifc4> file = IfcHierarchyHelper<Ifc4>(IfcParse::schema_by_name("IFC4"));
	file.header().file_name().name(filename);

	Ifc4::IfcRepresentationItem* csg1 = CSGBool::Box(8000.,6000.,3000.).subtract(
		CSGBool::Box(7600.,5600.,2800.).move(200.,200.,200.)
	).add(
		CSGBool::Pyramid(8000.,6000.,3000.).move(0,0,3000.).add(
			CSGBool::Cylinder(1000.,4000.).move(4000.,1000.,4000., 0.,1.,0.)
		).subtract(
			CSGBool::Pyramid(7600.,5600.,2800.).move(200.,200.,3000.)
		).subtract(
			CSGBool::Cylinder(900.,4000.).move(4000.,1000.,4000., 0.,1.,0.).intersect(
				CSGBool::Box(2000.,4000.,1000.).move(3000.,1000.,4000.)
			)
		)
	).serialize(file);

	const double x = 1000.; const double y = -4000.;
	
	Ifc4::IfcRepresentationItem* csg2 = CSGBool::Cone(5000., 6000.).move(x, y, -4500.).intersect(
		CSGBool::Box(6000., 6000., 6000.).move(x - 3000., y - 3000., 0.)
	).add(
		CSGBool::Cone(500., 3000.).move(x, y).add(
			CSGBool::Cone(1500., 1000.).move(x, y, 900.).add(
				CSGBool::Pyramid(1100., 1000., 6000.).move(x, y, 1800.).add(
					CSGBool::Cone(7500., 600.).move(x, y, 2700.)
				)))).serialize(file);

	Ifc4::IfcBuildingElementProxy* product = new Ifc4::IfcBuildingElementProxy(
		guid(), 0, S("IfcCsgPrimitive"), null, null, 0, 0, null, null);

	file.addBuildingProduct(product);

	product->setOwnerHistory(file.getSingle<Ifc4::IfcOwnerHistory>());

	product->setObjectPlacement(file.addLocalPlacement());

	Ifc4::IfcRepresentation::list::ptr reps(new Ifc4::IfcRepresentation::list());
	Ifc4::IfcRepresentationItem::list::ptr items(new Ifc4::IfcRepresentationItem::list());

	items->push(csg1);
	items->push(csg2);

	Ifc4::IfcShapeRepresentation* rep = new Ifc4::IfcShapeRepresentation(
		file.getSingle<Ifc4::IfcRepresentationContext>(), S("Body"), S("CSG"), items);
	reps->push(rep);

	Ifc4::IfcProductDefinitionShape* shape = new Ifc4::IfcProductDefinitionShape(null, null, reps);
	file.addEntity(rep);
	file.addEntity(shape);

	product->setRepresentation(shape);

	file.getSingle<Ifc4::IfcProject>()->setName("IfcCompositeProfileDef");

	std::ofstream f(filename);
	f << file;
}

Ifc4::IfcAxis2Placement3D* buildIfcAxis2Placement3D(DictionaryProperties& dictionaryProperties, IfcHierarchyHelper<Ifc4>& file) {

	double centroid_x = dictionaryProperties.getGraphicProperties()->getCentroid().x / 1000000;
	double centroid_y = dictionaryProperties.getGraphicProperties()->getCentroid().y / 1000000;
	double centroid_z = dictionaryProperties.getGraphicProperties()->getCentroid().z / 1000000;

	double z_axis_x = dictionaryProperties.getGraphicProperties()->getVectorAxisZ().x;
	double z_axis_y = dictionaryProperties.getGraphicProperties()->getVectorAxisZ().y;
	double z_axis_z = dictionaryProperties.getGraphicProperties()->getVectorAxisZ().z;

	double x_axis_x = dictionaryProperties.getGraphicProperties()->getVectorAxisX().x;
	double x_axis_y = dictionaryProperties.getGraphicProperties()->getVectorAxisX().y;
	double x_axis_z = dictionaryProperties.getGraphicProperties()->getVectorAxisX().z;


	Ifc4::IfcAxis2Placement3D* place = new Ifc4::IfcAxis2Placement3D(
		file.addTriplet<Ifc4::IfcCartesianPoint>(centroid_x, centroid_y, centroid_z),
		file.addTriplet<Ifc4::IfcDirection>(z_axis_x, z_axis_y, z_axis_z),
		file.addTriplet<Ifc4::IfcDirection>(x_axis_x, x_axis_y, x_axis_z)
	);
	return place;
}


#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4189)
Ifc4::IfcRepresentationItem* buildComplexPrimitive(DictionaryProperties& dictionaryProperties, Ifc4::IfcAxis2Placement3D* place, IfcHierarchyHelper<Ifc4>& file)
{
	Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* my = nullptr;

	
	if (dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::TORUS) {

		TorusGraphicProperties torusGraphicProperties;
		if (dictionaryProperties.getGraphicProperties()->tryGetTorusGraphicProperties(torusGraphicProperties)) 
		{
			Ifc4::IfcAxis2Placement2D* localPlacement = new Ifc4::IfcAxis2Placement2D(file.addDoublet<Ifc4::IfcCartesianPoint>(0, torusGraphicProperties.getMajorRadius()/1000000), 
				file.addTriplet<Ifc4::IfcDirection>(1, 0, 0));

			Ifc4::IfcCircleProfileDef* profileDef = new Ifc4::IfcCircleProfileDef(Ifc4::IfcProfileTypeEnum::IfcProfileType_AREA, boost::none, localPlacement, torusGraphicProperties.getMinorRadius()/1000000);
			Ifc4::IfcAxis1Placement* localAxis1Placement = new Ifc4::IfcAxis1Placement(file.addTriplet<Ifc4::IfcCartesianPoint>(0, 0, 0), file.addTriplet<Ifc4::IfcDirection>(1, 0, 0));

			my = new Ifc4::IfcRevolvedAreaSolid(profileDef, place, localAxis1Placement, torusGraphicProperties.getSweepRadians());
		}
		else
		{
			// TODO log sphere properties not found
		}
	}


	if (my != nullptr) {
		file.addEntity(my);

	}

	return my;

}

#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4189)
Ifc4::IfcRepresentationItem* buildPrimitive(DictionaryProperties& dictionaryProperties, Ifc4::IfcAxis2Placement3D* place, IfcHierarchyHelper<Ifc4>& file)
{
	Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* my = nullptr;

	if (dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::SPHERE) {

		SphereGraphicProperties sphereGraphicProperties;
		if (dictionaryProperties.getGraphicProperties()->tryGetSphereGraphicProperties(sphereGraphicProperties)) {
			my = new Ifc4::IfcSphere(place, sphereGraphicProperties.getRadius() / 1000000);
			Ifc4::IfcCsgSolid* solid = new Ifc4::IfcCsgSolid(my);
		}
		else
		{
			// TODO log sphere properties not found
		}
	}
	else if (dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::BOX) {
		/*my = new Ifc4::IfcBlock(place, a, b, c);*/
		SlabGraphicProperties slabGraphicProperties;
		if (dictionaryProperties.getGraphicProperties()->tryGetSlabProperties(slabGraphicProperties)) {
			my = new Ifc4::IfcBlock(place, slabGraphicProperties.getLength() / 1000000, slabGraphicProperties.getWidth() / 1000000, slabGraphicProperties.getHeight() / 1000000);
		}
		else {
			// TODO log slab properties not found
		}

	}
	//else if (dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::PYRAMID) {
	//	my = new Ifc4::IfcRectangularPyramid(place, a, b, c);
	//}
	else if (dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::CYLINDER) {
		CylinderGraphicProperties cylinderGraphicProperties;
		if (dictionaryProperties.getGraphicProperties()->tryGetCylinderGraphicProperties(cylinderGraphicProperties)) {
			my = new Ifc4::IfcRightCircularCylinder(place, cylinderGraphicProperties.getHeight() / 1000000, cylinderGraphicProperties.getRadius() / 1000000);
		}
		else {
			// TODO log cylinder properties not found
		}
	}
	else if (dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::CONE) {
		ConeGraphicProperties coneGraphicProperties;
		if (dictionaryProperties.getGraphicProperties()->tryGetConeGraphicProperties(coneGraphicProperties)) {
			/*my = new Ifc4::IfcRightCircularCone(place, dictionaryProperties.getGraphicProperties()->getHeight() / 100, dictionaryProperties.getGraphicProperties()->getRadius() / 100);*/
			my = new Ifc4::IfcRightCircularCone(place, coneGraphicProperties.getHeight() / 1000000, coneGraphicProperties.getBaseRadius() / 1000000);
		}
		else {
			// TODO log cone properties not found
		}

	}

	if (my != nullptr) {
		Ifc4::IfcCsgSolid* solid = new Ifc4::IfcCsgSolid(my);
		file.addEntity(my);
		return solid;

	}

	return nullptr;
	//items->push(solid);

}

void buildIfc(std::vector<DictionaryProperties*>& dictionaryPropertiesVector) {
	std::string name = "PrimitiveTest";
	IfcHierarchyHelper<Ifc4> file = IfcHierarchyHelper<Ifc4>(IfcParse::schema_by_name("IFC4"));
	//std::string filename = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/ifc/" + name + ".ifc";
	std::string filename = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/ifc/" + name + ".ifc";
	typedef Ifc4::IfcGloballyUniqueId guid2;

	//Ifc4::IfcSIUnit* ifcUnitLength = new Ifc4::IfcSIUnit(Ifc4::IfcUnitEnum::IfcUnit_LENGTHUNIT, Ifc4::IfcSIPrefix::IfcSIPrefix_CENTI, Ifc4::IfcSIUnitName::IfcSIUnitName_METRE);
	//Ifc4::IfcSIUnit* ifcUnitAngle = new Ifc4::IfcSIUnit(Ifc4::IfcUnitEnum::IfcUnit_PLANEANGLEUNIT, Ifc4::IfcSIPrefix::IfcSIPrefix_CENTI, Ifc4::IfcSIUnitName::IfcSIUnitName_RADIAN);
	Ifc4::IfcSIUnit* ifcUnitLength = new Ifc4::IfcSIUnit(Ifc4::IfcUnitEnum::IfcUnit_LENGTHUNIT, boost::none, Ifc4::IfcSIUnitName::IfcSIUnitName_METRE);
	Ifc4::IfcSIUnit* ifcUnitAngle = new Ifc4::IfcSIUnit(Ifc4::IfcUnitEnum::IfcUnit_PLANEANGLEUNIT, boost::none, Ifc4::IfcSIUnitName::IfcSIUnitName_RADIAN);

	//IfcEntityList entityList = new IfcEntityList();


	//std::vector<IfcUtil::IfcBaseClass*> ls;
	//ls.push_back(ifcUnitLength);
	//ls.push_back(ifcUnitAngle);
	//boost::shared_ptr<IfcEntityList> ceva = new 
	//boost::shared_ptr<void> p2(new int(5));

	IfcEntityList* entityList = new IfcEntityList();
	entityList->push(ifcUnitLength);
	entityList->push(ifcUnitAngle);
	boost::shared_ptr<IfcEntityList> unitEntity(entityList);
	//unitEntity->push(ifcUnitLength);
	//unitEntity->push(ifcUnitAngle);

	//vec.push_back(ifcUnitLength);
	//vec.push_back(ifcUnitAngle);

	Ifc4::IfcUnitAssignment* unitAssigment = new Ifc4::IfcUnitAssignment(unitEntity);
	//file.getRepresentationContext()-
	//file.getRepresentationContext()->;
	Ifc4::IfcProject* project = new Ifc4::IfcProject(guid2::IfcGloballyUniqueId(name), file.getSingle<Ifc4::IfcOwnerHistory>(), boost::none, boost::none, boost::none, boost::none, boost::none, boost::none, unitAssigment);

	file.addEntity(project);
	//file.getSingle<Ifc4::IfcProject>();
	

	//file.addEntity(unitAssigment);
	//file.getRepresentationContext()

	Ifc4::IfcRepresentation::list::ptr reps(new Ifc4::IfcRepresentation::list());
	Ifc4::IfcRepresentationItem::list::ptr items(new Ifc4::IfcRepresentationItem::list());

	Ifc4::IfcBuildingElementProxy* primitive = new Ifc4::IfcBuildingElementProxy(
		guid2::IfcGloballyUniqueId(name),
		0,
		name,
		boost::none,
		boost::none,
		0,
		0,
		boost::none,
		boost::none
	);

	file.addBuildingProduct(primitive);

	primitive->setOwnerHistory(file.getSingle<Ifc4::IfcOwnerHistory>());
	primitive->setObjectPlacement(file.addLocalPlacement());

	for (int i = 0; i < dictionaryPropertiesVector.size(); ++i) {
		DictionaryProperties& dictionaryProperties = *dictionaryPropertiesVector.at(i);

		if (dictionaryProperties.getGeneralProperties()->getIsSmartFeature()) {
			continue;
		}
		Ifc4::IfcAxis2Placement3D* place = buildIfcAxis2Placement3D(dictionaryProperties, file);

		Ifc4::IfcRepresentationItem* item = nullptr;
		if (dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::SPHERE || dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::BOX||
			dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::CONE || dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::CYLINDER) 
		{
			item = buildPrimitive(dictionaryProperties, place, file);
		}
		else if (dictionaryProperties.getGeneralProperties()->getPrimitiveTypeEnum() == PrimitiveTypeEnum::PrimitiveTypeEnum::TORUS) 
		{
			item = buildComplexPrimitive(dictionaryProperties, place, file);
		}

		if (item == nullptr) {
			continue;
		}
		items->push(item);

		Ifc4::IfcShapeRepresentation* rep = new Ifc4::IfcShapeRepresentation(
			file.getSingle<Ifc4::IfcGeometricRepresentationContext>(), std::string("Body") + std::to_string(i), std::string("Model") + std::to_string(i), items);

		reps->push(rep);

		file.addEntity(rep);
	}
	

	Ifc4::IfcProductDefinitionShape* shape = new Ifc4::IfcProductDefinitionShape(boost::none, boost::none, reps);

	file.addEntity(shape);

	primitive->setRepresentation(shape);

	std::ofstream f;
	f.open(filename);
	f << file;
	f.close();
}

#pragma warning( push )
#pragma warning( disable : 4700)
#pragma warning( disable : 4189)
StatusInt GetSmartFeatureTree(WCharCP unparsedP)
{
	DgnModelP dgnModel = ISessionMgr::GetActiveDgnModelP();
	std::ofstream outfile;
	//std::string filePath = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/TEST.txt";
	std::string filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";

	WString myString, sFeatTree;
	WString dgnFileName = ISessionMgr::GetActiveDgnFile()->GetFileName().AppendUtf8(".txt");

	std::cout << filePath << std::endl;

	// Create the instance for the Graphics Processor
	GraphicsProcessor graphicsProcessor = GraphicsProcessor(outfile, filePath);

	PersistentElementRefList *pGraElement = dgnModel->GetGraphicElementsP();
	outfile.open(filePath);
	outfile << "===================================================" << std::endl;
	outfile.close(); 

	std::vector<DictionaryProperties*>propsDictVec;
	SmartFeatureContainer* smartFeatureContainer = new SmartFeatureContainer();
	
	for (PersistentElementRefP elemRef : *pGraElement)
	{
		ElementHandle leafNode;
		ElementHandle currentElem(elemRef);
		SmartFeatureNodePtr sFeatNode;
		T_SmartFeatureVector sFeatVec;
		WString elDescr;

		currentElem.GetHandler().GetDescription(currentElem, elDescr, 100);
		
		long newCurrentElementId = -1, newLocalNodeId = -1, newParentLocalNodeId = -1, newLeafElementId=-1;

		newCurrentElementId = currentElem.GetElementId();
		if (SmartFeatureElement::IsSmartFeature(currentElem))
		{
			SmartFeatureElement::ExtractTree(sFeatNode, currentElem);

			sFeatNode->GetAllChildrenRecursively(sFeatVec);
			
			for (size_t i = 0; i < sFeatVec.size(); i++)
			{
				outfile.open(filePath, std::ios_base::app);
				outfile << "start==================" << std::endl;
				outfile.close();
				if (sFeatVec.at(i)->GetParent() != nullptr)
				{						
					outfile.open(filePath, std::ios_base::app);

					outfile << "Parent Ref Count: " << sFeatVec.at(i)->GetParent()->GetRefCount() << std::endl;
					outfile << "Parent ID: " << sFeatVec.at(i)->GetParent()->GetNodeId() << std::endl;
					outfile.close();
					
					newParentLocalNodeId = sFeatVec.at(i)->GetParent()->GetNodeId();
				}

				newLocalNodeId = sFeatVec.at(i)->GetNodeId();

				outfile.open(filePath, std::ios_base::app);
				outfile << "Node ID: " << newLocalNodeId << std::endl;
				outfile.close();
								
				sFeatVec.at(i)->GetLeaf(leafNode);

				if (leafNode.IsValid()) {

					newLeafElementId = leafNode.GetElementId();
					
					outfile.open(filePath, std::ios_base::app);

					outfile.open(filePath, std::ios_base::app);
					outfile << "Leaf ID:  " << leafNode.GetElementId() << std::endl;				
					outfile.close();
				}
				outfile.open(filePath, std::ios_base::app);

				outfile << "finish==================" << std::endl;
				outfile.close();

				smartFeatureContainer->insertNodeInTree(newCurrentElementId, newLocalNodeId, newParentLocalNodeId, newLeafElementId);
			}
			outfile.open(filePath, std::ios_base::app);

			outfile.open(filePath, std::ios_base::app);
			outfile << "Smart Feat Element Node ID: " << sFeatNode->GetNodeId() << std::endl;
			outfile << "Number of Child: " << sFeatNode->GetChildCount() << std::endl;
			outfile.close();
		}


		outfile.open(filePath, std::ios_base::app);
		outfile << "===================================================" << std::endl;
		outfile << "===================================================" << std::endl;
		outfile << "Element Description: " << static_cast<Utf8String>(elDescr.GetWCharCP())<< std::endl;
		outfile << "Element ID: " << currentElem.GetElementId() << std::endl;
		outfile << "===================================================" << std::endl;
		outfile << "===================================================" << std::endl;
		outfile << std::endl;
		outfile.close();

		DictionaryProperties* propertiesDictionary = new DictionaryProperties();
		propertiesDictionary->getGeneralProperties()->setPrimitiveTypeEnum(PrimitiveTypeEnumUtils::getPrimitiveTypeEnumByElementDescription(StringUtils::getString(elDescr.GetWCharCP())));


		propertiesDictionary->getGeneralProperties()->setClassName(StringUtils::getString(elDescr.GetWCharCP()));
		propertiesDictionary->getGeneralProperties()->setElementId(currentElem.GetElementId());
		propertiesDictionary->getGeneralProperties()->setCurrentElementId(currentElem.GetElementId());
		
		PropertiesReaderProcessor* propertiesReaderProcessor = new PropertiesReaderProcessor(currentElem, outfile, filePath, *propertiesDictionary,*smartFeatureContainer);

		graphicsProcessor.setPropertiesDictionary(propertiesDictionary);
		graphicsProcessor.updateClassAndID(propertiesReaderProcessor->getElemClassName(), currentElem.GetElementId());
		ElementGraphicsOutput::Process(currentElem, graphicsProcessor);

		propsDictVec.push_back(propertiesDictionary);

	}

	std::vector<DictionaryProperties*> newPropsDictVec;
	auto iterator = propsDictVec.begin();

	for (int i = 0; i < propsDictVec.size(); ++i) {
		DictionaryProperties* propertiesDictionary = propsDictVec.at(i);
		if (propertiesDictionary->getIsSmartFeatureMissingReaderProperties()) {
			SmartFeatureTreeNode* treeNode = smartFeatureContainer->searchByElementGlobalId(smartFeatureContainer->getRoot(), propertiesDictionary->getGeneralProperties()->getElementId());
			if (treeNode != nullptr) {
				treeNode->setGraphicProperties(propertiesDictionary->getGraphicProperties());
				treeNode->getGeneralProperties()->setPrimitiveTypeEnum(propertiesDictionary->getGeneralProperties()->getPrimitiveTypeEnum());
			}
		}	
		else if (smartFeatureContainer->searchByElementGlobalId(smartFeatureContainer->getRoot(), propertiesDictionary->getGeneralProperties()->getElementId()) != nullptr)
		{
			continue;
		}
		else if (propertiesDictionary->getGeneralProperties()->getIsSmartFeature())
		{
			continue;
		}
		else
		{
			newPropsDictVec.push_back(propertiesDictionary);
		}
		iterator++;
	}

	propsDictVec.clear();
	
	IfcDataHandler ifcDataHandler = IfcDataHandler(newPropsDictVec, smartFeatureContainer);
	//buildIfc(newPropsDictVec);
	//test();
	//buildPrimitive(propsDictVec);

	outfile.close();

	return SUCCESS;
}
#pragma warning( pop ) 


/*=================================================================================**//**
* @description  Unload this application
* @param[in] unparsed Additional input supplied after command string.
+===============+===============+===============+===============+===============+======*/
void UnloadParametricFeatures(WCharCP unparsedP)
{
	auto taskID = mdlSystem_getCurrTaskID();
	mdlDialog_cmdNumberQueue(FALSE, CMD_MDL_UNLOAD, taskID, INPUTQ_HEAD); //INPUTQ_EOQ
	return;
}
