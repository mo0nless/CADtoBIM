#include "../headers/IfcGenerator.h"

IfcGenerator::IfcGenerator(std::vector<DictionaryProperties*> dictProps, SmartFeatureContainer * smartContainer):
	dictionaryProperties(dictProps), smartFeatContainer(smartContainer)
{	
	if (smartFeatContainer->getRoot() != nullptr)
	{
		ReverseLevelOrder();
	}
}

Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem * IfcGenerator::PrimitivesMapperSwitch(SmartFeatureTreeNode* treeNode)
{
	double a = 50, b = 50, c = 50;
	Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* my = nullptr;
	Ifc4::IfcAxis2Placement3D* place = nullptr;

	GraphicProperties* graphicProps = treeNode->getGraphicProperties();
	PrimitiveTypeEnum::PrimitiveTypeEnum primitiveType = treeNode->getGeneralProperties()->getPrimitiveTypeEnum();

	if (primitiveType == PrimitiveTypeEnum::PrimitiveTypeEnum::SPHERE) {
		my = new Ifc4::IfcSphere(place, a);
	}
	else if (primitiveType == PrimitiveTypeEnum::PrimitiveTypeEnum::BOX) {
		DVec3d objectOrigin = graphicProps->getCentroid() / 100;
		DVec3d vectorBaseX = graphicProps->getVectorAxisX();

		DVec3d vectorBaseZ = graphicProps->getVectorAxisZ();


		vectorBaseX.Normalize();
		vectorBaseZ.Normalize();

		place = new Ifc4::IfcAxis2Placement3D(
			file.addTriplet<Ifc4::IfcCartesianPoint>(objectOrigin.x, objectOrigin.y, objectOrigin.z),
			file.addTriplet<Ifc4::IfcDirection>(vectorBaseZ.x, vectorBaseZ.y, vectorBaseZ.z),
			file.addTriplet<Ifc4::IfcDirection>(vectorBaseX.x, vectorBaseX.y, vectorBaseX.z)
		);
		my = new Ifc4::IfcBlock(place,100,100,100);
	}
	else if (primitiveType == PrimitiveTypeEnum::PrimitiveTypeEnum::PYRAMID) {
		my = new Ifc4::IfcRectangularPyramid(place, a, b, c);
	}
	else if (primitiveType == PrimitiveTypeEnum::PrimitiveTypeEnum::CYLINDER) {
		my = new Ifc4::IfcRightCircularCylinder(place, b, a);
	}
	else if (primitiveType == PrimitiveTypeEnum::PrimitiveTypeEnum::CONE) {
		my = new Ifc4::IfcRightCircularCone(place, b, a);
	}

	file.addEntity(my);

	return my;
}

void IfcGenerator::ReverseLevelOrder()
{
	SmartFeatureTreeNode* treeRoot = smartFeatContainer->getRoot();
	std::queue <SmartFeatureTreeNode*> queueSmartFeature;

	if (treeRoot != nullptr)
	{
		queueSmartFeature.push(treeRoot);

		while (queueSmartFeature.empty() == false)
		{
			treeRoot = queueSmartFeature.front();
			queueSmartFeature.pop();
			stackSmartFeature.push(treeRoot);

			if (treeRoot->getRightNode())
			{
				queueSmartFeature.push(treeRoot->getRightNode());
			}

			if (treeRoot->getLeftNode())
			{
				queueSmartFeature.push(treeRoot->getLeftNode());
			}
		}
	}

	SmartFeatureBooleanOperations();
}

void IfcGenerator::SmartFeatureBooleanOperations()
{
	SmartFeatureTreeNode* rightNode;
	SmartFeatureTreeNode* leftNode;
	SmartFeatureTreeNode* parentNode = nullptr;

	//bool isNestedParentInSmartFeature = false;
	typedef Ifc4::IfcGloballyUniqueId guid;

	std::string name = "PrimitiveTest";
	std::string filename = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/ifc/" + name + ".ifc";
	//std::string filename = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/ifc/" + name + ".ifc";

	Ifc4::IfcBooleanOperator::Value ifcOperatorBool;

	Ifc4::IfcRepresentation::list::ptr reps(new Ifc4::IfcRepresentation::list());
	Ifc4::IfcRepresentationItem::list::ptr items(new Ifc4::IfcRepresentationItem::list());

	Ifc4::IfcBuildingElementProxy* primitive = new Ifc4::IfcBuildingElementProxy(
		guid::IfcGloballyUniqueId(name),
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

	Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* csgRightNode = nullptr;
	Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* csgLeftNode = nullptr;

	Ifc4::IfcCsgPrimitive3D::IfcGeometricRepresentationItem* csgBooleanParentNode = nullptr;

	//Ifc4::IfcCsgSolid* firstSolid = nullptr;
	//Ifc4::IfcCsgSolid* secondSolid = nullptr;
	Ifc4::IfcCsgSolid* booleanSolid = nullptr;
	Ifc4::IfcShapeRepresentation* rep = nullptr;
		
	while (stackSmartFeature.empty() == false)
	{
		rightNode = stackSmartFeature.top();
		stackSmartFeature.pop();
		csgRightNode = PrimitivesMapperSwitch(rightNode);

		leftNode = stackSmartFeature.top();
		stackSmartFeature.pop();
		csgLeftNode = PrimitivesMapperSwitch(leftNode);

		long parentID = rightNode->getGeneralProperties()->getLocalParentNodeId();

		parentNode = smartFeatContainer->searchByElementLocalNodeId(smartFeatContainer->getRoot(), parentID);

		if (parentNode->getGeneralProperties()->getIsSmartFeature())
		{
			BooleanFunctions::BooleanFunctionsEnum currentBooleanOperation = parentNode->getReaderProperties()->getBooleanFunction();

			if (currentBooleanOperation == BooleanFunctions::BooleanFunctionsEnum::UNION) {
				ifcOperatorBool = Ifc4::IfcBooleanOperator::IfcBooleanOperator_UNION;
			}
			else if (currentBooleanOperation == BooleanFunctions::BooleanFunctionsEnum::DIFFERENCE) {
				ifcOperatorBool = Ifc4::IfcBooleanOperator::IfcBooleanOperator_DIFFERENCE;
			}
			else if (currentBooleanOperation == BooleanFunctions::BooleanFunctionsEnum::INTERSECTION) {
				ifcOperatorBool = Ifc4::IfcBooleanOperator::IfcBooleanOperator_INTERSECTION;
			}

			csgBooleanParentNode = new Ifc4::IfcBooleanResult(ifcOperatorBool, csgRightNode, csgLeftNode);

			booleanSolid = new Ifc4::IfcCsgSolid(csgBooleanParentNode);

			file.addEntity(csgBooleanParentNode);
			items->push(booleanSolid);

			rep = new Ifc4::IfcShapeRepresentation(
				file.getSingle<Ifc4::IfcGeometricRepresentationContext>(), std::string("Body"), std::string("Model"), items);

			reps->push(rep);

			file.addEntity(rep);

			parentNode = smartFeatContainer->searchByElementLocalNodeId(smartFeatContainer->getRoot(), parentNode->getGeneralProperties()->getLocalParentNodeId());
			
			if (parentNode == nullptr)
			{
				stackSmartFeature.pop();
			}
		}
	}
	

	//file.addEntity(reps);

	Ifc4::IfcProductDefinitionShape* shape = new Ifc4::IfcProductDefinitionShape(boost::none, boost::none, reps);

	file.addEntity(shape);

	primitive->setRepresentation(shape);

	std::ofstream f;
	f.open(filename);
	f << file;
	f.close();
}
