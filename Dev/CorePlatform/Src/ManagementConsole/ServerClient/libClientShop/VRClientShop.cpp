#include "VRClient.h"
#include "VRShoppingPlace_GUI.h"

#include "VRClientShop.h"

using namespace VR;

//----------------------------------------------------------------------

ClientShop::ClientShop() :
m_pClient(0), m_pShoppingPlace_GUI(0)	{

}

//----------------------------------------------------------------------

ClientShop::~ClientShop()	{
	if (m_pClient)
		delete m_pClient;
	if (m_pShoppingPlace_GUI)
		delete m_pShoppingPlace_GUI;
}

//=====================================================================

bool ClientShop::initializeClient()	{
	bool bRes=false;
	return bRes;
}

//----------------------------------------------------------------------

bool ClientShop::createNewClientGUI()	{
	bool bRes = false;
	return bRes;
}