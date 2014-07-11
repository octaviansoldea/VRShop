#include "VRAbstractUser.h"
#include "VRVisitor.h"

#include "VRAgentManager.h"

#include <string>

using namespace VR;
using namespace std;

//==============================================================================

AgentManager::AgentManager()	{
}

//------------------------------------------------------------------------------

AgentManager::~AgentManager()	{
	list<AbstractUser*>::iterator it = m_lstUsers.begin();
	for(it; it != m_lstUsers.end(); ++it)	{
		AbstractUser * pAU = (AbstractUser*)(*it);
		delete pAU;
		pAU = 0;
	}
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

long AgentManager::getNumberOfUsers() const	{
	return m_lstUsers.size();
}