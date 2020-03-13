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


SmartFeatureContainer* createSmartFeatureContainer(ElementHandle currentElem, SmartFeatureNodePtr sFeatNode, ElementHandle leafNode, T_SmartFeatureVector sFeatVec) {
	std::ofstream outfile;
	//std::string filePath = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/TEST.txt";
	std::string filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.txt";

	SmartFeatureContainer* smartFeatureContainer = new SmartFeatureContainer();
	long newCurrentElementId = -1, newLocalNodeId = -1, newParentLocalNodeId = -1, newLeafElementId = -1;
	newCurrentElementId = currentElem.GetElementId();
	
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
	

	return smartFeatureContainer;
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
	std::vector<SmartFeatureContainer*> smartFeatureContainerVector;
	
	
	for (PersistentElementRefP elemRef : *pGraElement)
	{
		ElementHandle leafNode;
		ElementHandle currentElem(elemRef);
		SmartFeatureNodePtr sFeatNode;
		T_SmartFeatureVector sFeatVec;
		WString elDescr;

		currentElem.GetHandler().GetDescription(currentElem, elDescr, 100);
		SmartFeatureContainer* smartFeatureContainer = nullptr;

		if (SmartFeatureElement::IsSmartFeature(currentElem))
		{
			smartFeatureContainer = createSmartFeatureContainer(currentElem, sFeatNode, leafNode, sFeatVec);
			if (smartFeatureContainer != nullptr) 
			{
				smartFeatureContainerVector.push_back(smartFeatureContainer);
			}
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
		
		
		PropertiesReaderProcessor* propertiesReaderProcessor = new PropertiesReaderProcessor(currentElem, outfile, filePath, *propertiesDictionary, *smartFeatureContainer);


		graphicsProcessor.setPropertiesDictionary(propertiesDictionary);
		graphicsProcessor.updateClassAndID(propertiesReaderProcessor->getElemClassName(), currentElem.GetElementId());
		ElementGraphicsOutput::Process(currentElem, graphicsProcessor);

		propsDictVec.push_back(propertiesDictionary);

	}

	std::vector<DictionaryProperties*> newPropsDictVec;

	if (smartFeatureContainerVector.empty()) {
		newPropsDictVec = propsDictVec;
	}
	else 
	{
		for (int i = 0; i < propsDictVec.size(); ++i) {
			DictionaryProperties* propertiesDictionary = propsDictVec.at(i);

			for (int j = 0; j < smartFeatureContainerVector.size(); ++j) {
				SmartFeatureContainer* smartFeatureContainer = smartFeatureContainerVector.at(j);

				if (propertiesDictionary->getAreReaderPropertiesFound()) {
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
			}

		}
	}

	

	propsDictVec.clear();
	
	IfcBuilder* ifcBuilder = new IfcBuilder();
	ifcBuilder->buildIfc(newPropsDictVec, smartFeatureContainerVector);



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
