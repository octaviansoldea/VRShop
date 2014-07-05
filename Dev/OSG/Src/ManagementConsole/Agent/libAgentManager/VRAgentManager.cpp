#include "VRAgentManager.h"

#include <string>

using namespace VR;
using namespace std;

//==============================================================================

AgentManager::AgentManager()	{
}

//------------------------------------------------------------------------------

AgentManager::~AgentManager()	{
}

//------------------------------------------------------------------------------

const char* AgentManager::className() const	{
	return "AgentManager";
}

//------------------------------------------------------------------------------

bool AgentManager::newUserRequest()	{
	bool bRes = false;

	//If all steps pass, return true and proceed

	// else send to the server a denial which is passed to the user

	return bRes;
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

long AgentManager::getNumberOfUsers() const	{
	return m_lstUsers.size();
}