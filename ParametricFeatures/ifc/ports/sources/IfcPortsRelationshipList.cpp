#include "../headers/IfcPortsRelationshipList.h"

IfcPortsRelationshipList::IfcPortsRelationshipList()
{
	mHead = NULL;
}



bool IfcPortsRelationshipList::connectPortAtLocation(PortElement*& newPortElement)
{
	vector<double> pointCurrent;
	vector<double> pointNew = newPortElement->cartesianPointPort->Coordinates();
	
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
		//Check the equality of the ports
		connected = Comparator::isEqual(pointCurrent, pointNew);

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
	ofstream outfile;
	string filePath = SessionManager::getInstance()->getDataOutputFilePath();


	PortElement *temp = new PortElement;
	temp = mHead;
	while (temp != NULL)
	{
		bool connection = temp->isElementConnected;
		if (connection)
		{
			vector<double> point = temp->cartesianPointPort->Coordinates();
		
			outfile.open(filePath, ios_base::app);
			outfile << fixed;

			outfile << "Port Name  = " << temp->distributionPort->Name() << endl;
			outfile << "Element ID  = " << temp->elementIdNumber << endl;
			outfile << "Point  X = " << point[0] << endl;
			outfile << "Point  Y = " << point[1] << endl;
			outfile << "Point  Z = " << point[2] << endl;
			outfile << endl;
			
			temp = temp->nextPortElement;

		
			point = temp->cartesianPointPort->Coordinates();
			
			outfile << "Next Connected Port Name  = " << temp->distributionPort->Name() << endl;
			outfile << "Element ID  = " << temp->elementIdNumber << endl;
			outfile << "Next Point  X = " << point[0] << endl;
			outfile << "Next Point  Y = " << point[1] << endl;
			outfile << "Next Point  Z = " << point[2] << endl;
			outfile << endl;
		}
		else
			temp = temp->nextPortElement;		

		outfile.close(); 
	}
}