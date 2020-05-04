#include "../headers/IfcPortsRelationshipList.h"

IfcPortsRelationshipList::IfcPortsRelationshipList()
{
	mHead = NULL;
}


bool IfcPortsRelationshipList::isDoubleEqual(double x, double y)
{
	/* some small number such as 1e-5 */
	const double epsilon = 1e-5;
	return std::abs(x - y) <= epsilon * std::abs(x);
	// see Knuth section 4.2.2 pages 217-218
}

bool IfcPortsRelationshipList::isEqual(std::vector<double> v1, std::vector<double>  v2)
{
	if (v1.size() == v2.size())
	{
		for (size_t i = 0; i < v1.size(); i++)
		{
			if (isDoubleEqual(v1[i], v2[i]))
				continue;
			else
				return false;
		}
		return true;
	}

	return false;
}

bool IfcPortsRelationshipList::connectPortAtLocation(PortElement*& newPortElement)
{
	std::vector<double> pointCurrent;
	std::vector<double> pointNew = newPortElement->cartesianPointPort->Coordinates();
	
	PortElement *temp;
	PortElement *tempLast = NULL;
	bool connected = false;
	
	// Point temp to start 
	temp = mHead;
		
	// Iterate till the loc 
	while (temp != NULL)
	{
		//check if the temp element is connected to the current one
		pointCurrent = temp->cartesianPointPort->Coordinates();
		connected = isEqual(pointCurrent, pointNew);

		if (connected) {
			temp->isElementConnected = connected;
			break;
		}
		else
			tempLast = temp;
			temp = temp->nextPortElement;
	}

	if (connected)
	{
		//Check if it's in between the list the connection
		if (temp->nextPortElement != NULL)
		{
			newPortElement->nextPortElement = temp->nextPortElement;
			(temp->nextPortElement)->previousPortElement = newPortElement;
			temp->nextPortElement = newPortElement;
			newPortElement->previousPortElement = temp;
		}
		else
		{
			newPortElement->previousPortElement = temp;
			temp->nextPortElement = newPortElement;

			//flag that the last element is the connection
			temp->isElementConnected = connected;
		}
		

		return true;
	}
	//If it's not connected added last
	else
	{
		newPortElement->previousPortElement = tempLast;
		tempLast->nextPortElement = newPortElement;
		
		return true;
	}
	
	

	return false;
}

PortElement* IfcPortsRelationshipList::getHead()
{
	return this->mHead;
}

void IfcPortsRelationshipList::insertIfcPortElement(Ifc4::IfcCartesianPoint* point, Ifc4::IfcDistributionPort* dPort, IfcElementBundle*& ifcElementBundle)
{
	PortElement* newPortElement = new PortElement;
		
	//Data filling for the new element
	newPortElement->cartesianPointPort = point;
	newPortElement->distributionPort = dPort;
	newPortElement->elementIdNumber = ifcElementBundle->getModelerElementId();
	newPortElement->ifcDistributionElement = (Ifc4::IfcDistributionElement*)ifcElementBundle->getIfcElement();

	newPortElement->nextPortElement = NULL;
	newPortElement->previousPortElement = NULL;
	newPortElement->isElementConnected = false;

	if (mHead == NULL)
	{
		mHead = newPortElement;
	}
	else
	{
		connectPortAtLocation(newPortElement);
	}
}

void IfcPortsRelationshipList::display()
{
	std::ofstream outfile;
	//std::string filePath = "C:/Users/LX5990/source/repos/CADtoBIM/ParametricFeatures/examples/TEST.txt";
	std::string filePath = "C:/Users/FX6021/source/repos/cadtobim/ParametricFeatures/examples/TEST.text";


	PortElement *temp = new PortElement;
	temp = mHead;
	while (temp != NULL)
	{
		bool connection = temp->isElementConnected;
		if (connection)
		{
			std::vector<double> point = temp->cartesianPointPort->Coordinates();
		
			outfile.open(filePath, std::ios_base::app);
			outfile << std::fixed;

			outfile << "Port Name  = " << temp->distributionPort->Name() << std::endl;
			outfile << "Element ID  = " << temp->elementIdNumber << std::endl;
			outfile << "Point  X = " << point[0] << std::endl;
			outfile << "Point  Y = " << point[1] << std::endl;
			outfile << "Point  Z = " << point[2] << std::endl;
			outfile << std::endl;
			
			temp = temp->nextPortElement;

		
			point = temp->cartesianPointPort->Coordinates();
			
			outfile << "Next Connected Port Name  = " << temp->distributionPort->Name() << std::endl;
			outfile << "Element ID  = " << temp->elementIdNumber << std::endl;
			outfile << "Next Point  X = " << point[0] << std::endl;
			outfile << "Next Point  Y = " << point[1] << std::endl;
			outfile << "Next Point  Z = " << point[2] << std::endl;
			outfile << std::endl;
		}
		else
			temp = temp->nextPortElement;		

		outfile.close(); 
	}
}