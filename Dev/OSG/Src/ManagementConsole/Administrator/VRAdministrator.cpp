#include "VRServer_GUI.h"
#include "VRAgentManager.h"

#include "VRAdministrator.h"

using namespace VR;

//----------------------------------------------------------------------

Administrator::Administrator(QObject * parent) : QObject(parent)	{
	m_pServer_GUI = 0;
	m_pAgentManager = 0;
}

//----------------------------------------------------------------------

Administrator::~Administrator()	{
	delete m_pServer_GUI;
	delete m_pAgentManager;
}

//======================================================================

bool Administrator::runServer()	{
	bool bRes=true;

	bRes = m_Server.init();

	if (bRes)	{
		m_pServer_GUI = new Server_GUI(&m_Server);
		m_pServer_GUI->show();
	}

	return bRes;
}

//---------------------------------------------------------------------

void Administrator::closeServer()	{
	m_pServer_GUI->close();
}

//---------------------------------------------------------------------

bool Administrator::activateAgentManager()	{
	bool bRes = false;

	m_pAgentManager = new AgentManager();

	return bRes;
}

//---------------------------------------------------------------------

void Administrator::slotNewUser()	{
}