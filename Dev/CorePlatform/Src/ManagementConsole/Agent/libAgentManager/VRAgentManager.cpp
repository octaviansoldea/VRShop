#include "VRAbstractUser.h"
#include "VRVisitor.h"

#include "VRClient.h"

#include "VRAgentManager.h"

#include <string>

using namespace VR;
using namespace std;

//==============================================================================

AgentManager::AgentManager()	{
	m_pClient = new Client(0);
}

//------------------------------------------------------------------------------

AgentManager::~AgentManager()	{
	list<AbstractUser*>::iterator it = m_lstUsers.begin();
	for(it; it != m_lstUsers.end(); ++it)	{
		AbstractUser * pAU = (AbstractUser*)(*it);
		delete pAU;
		pAU = 0;
	}

	delete m_pClient;
}

//------------------------------------------------------------------------------

const char* AgentManager::className() const	{
	return "AgentManager";
}

//------------------------------------------------------------------------------

void AgentManager::addUser(AbstractUser * apAbstractUser)	{
	if (apAbstractUser == 0)	{
		return;
	} else {
		m_lstUsers.push_back(apAbstractUser);
	}
}

//------------------------------------------------------------------------------

void AgentManager::removeUser(AbstractUser * apAbstractUser)	{
	m_lstUsers.remove(apAbstractUser);
}

//------------------------------------------------------------------------------

void AgentManager::updateUser(AbstractUser * apAbstractUser)	{
}

//------------------------------------------------------------------------------

void AgentManager::userChangedStatus(AbstractUser * apAbstractUser)	{
}

//------------------------------------------------------------------------------

long AgentManager::getNumberOfUsers() const	{
	return m_lstUsers.size();
}

//------------------------------------------------------------------------------

void AgentManager::trySigningIn(const string & astrUserName, const string & astrPassword)	{
	//Here establish client - server communication
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out.setVersion(QDataStream::Qt_4_8);

	QString qstrUser = (astrUserName + ";" + astrPassword).c_str();

	out << quint64(0) << quint8('U') << qstrUser;

	///*
	//	PATTERN:	
	//		quint64(0)  - size
	//		quint8('P') - product
	//		quint8('A') - avatar
	//		quint8('U') - signIn
	//		request
	//*/

	m_pClient->sendRequest(block);
}