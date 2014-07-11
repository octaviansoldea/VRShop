#include "VRServer_GUI.h"
#include "VRAgentManager.h"
#include "VRVisitor.h"

#include "VRCentralControl.h"

using namespace VR;

//----------------------------------------------------------------------

CentralControl::CentralControl(QObject * parent) : QObject(parent)	{
	m_Server.init();

	m_pServer_GUI = new Server_GUI(&m_Server);
	m_pServer_GUI->show();

	connect(&m_Server,SIGNAL(newConnection()),this, SLOT(slotNewUserRequest()));

	m_pAgentManager = new AgentManager();
}

//----------------------------------------------------------------------

CentralControl::~CentralControl()	{
	delete m_pServer_GUI;
	delete m_pAgentManager;
}

//======================================================================

void CentralControl::closeServer()	{
	m_pServer_GUI->close();
}

//---------------------------------------------------------------------

void CentralControl::slotNewUserRequest()	{
	
	Visitor * pVisitor = new Visitor();
	m_pAgentManager->addUser(pVisitor);

}