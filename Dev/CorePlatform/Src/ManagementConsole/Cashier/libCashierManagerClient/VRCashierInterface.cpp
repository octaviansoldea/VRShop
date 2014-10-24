#include <string>
#include <iostream>
#include "BasicStringDefinitions.h"

#include "VRServerClientCommands.h"

#include "VRCashierManagerClient.h"

#include "VRCashierInterface.h"

using namespace VR;
using namespace std;


CashierInterface::CashierInterface()	{
	m_pCashierManagerClient = new CashierManagerClient();
}

//----------------------------------------------------------------------

CashierInterface::~CashierInterface()	{
	delete m_pCashierManagerClient;
}

//=======================================================================

void CashierInterface::proceedPayClicked(list<pair<string,float>> & alstBasketContent)	{
	//string strRequestData = "";
	//list<pair<string,float>>::iterator it = alstBasketContent.begin();
	//for (it; it != alstBasketContent.end(); it++)	{
	//	strRequestData += it->first + ";" + tostr(it->second) + ";";
	//}
	//strRequestData.pop_back();

	//CashierManagerClient::CashierManagerClientParams cmcParams;
	//cmcParams.m_strVisitorName; // = m_pVisitor->getUserIDName();

	//m_pCashierManagerClient->requestToServer(ServerClientCommands::PURCHASE_REQUEST,&cmcParams);
}

//----------------------------------------------------------------------

void CashierInterface::moreInfoClicked(const int & anProductID)	{
}
