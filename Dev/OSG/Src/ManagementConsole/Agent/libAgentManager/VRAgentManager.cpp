#include "VRAgentManager.h"

#include <vector>
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

void AgentManager::addUser(AbstractUser * apAbstractUser)	{
	if (apAbstractUser == 0)	{
		return;
	} else {
		m_vecUsers.push_back(apAbstractUser);
	}
}

//------------------------------------------------------------------------------

void AgentManager::removeUser(AbstractUser * apAbstractUser)	{
}

//------------------------------------------------------------------------------

long AgentManager::getNumberOfUsers() const	{
	return m_vecUsers.size();
}