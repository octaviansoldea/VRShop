#include <iostream>
#include <fstream>

#include <vector>

#include "BasicStringDefinitions.h"

#include "VRAppDataServer.h"

#include "VRCashierServerReport.h"

using namespace VR;
using namespace std;

//=============================================================================

CashierServerReport::CashierServerReport()	{
}

//=============================================================================

void CashierServerReport::createOrdersReportHeader(list<string> & alststrOrdersData, std::ofstream & aOutputFile)	{
	aOutputFile << "ORDERS:" << endl;
	aOutputFile << "================================================" << endl;
	aOutputFile << "CUSTOMER" << endl;
}

//-----------------------------------------------------------------------------

void CashierServerReport::createOrdersReportCustomer(std::string & astrOrdersData, std::ofstream & aOutputFile)	{
	vector<string> vecstrCustomerData = splitString(astrOrdersData, ";");

	if (vecstrCustomerData.size() == 0)	{
		return;
	}

	vector<string>::iterator it = vecstrCustomerData.begin();

	for (it; it != vecstrCustomerData.end(); it++)	{
		aOutputFile << *it << ", ";
	}

	aOutputFile << endl;
}

//-----------------------------------------------------------------------------

void CashierServerReport::createOrdersReportListProducts(std::list<std::string> & alststrOrdersData, std::ofstream & aOutputFile)	{
}